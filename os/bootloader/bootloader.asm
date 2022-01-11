org 0x7c00
bits 16

%define ENDL 0x0D, 0x0A

jmp start
nop
bpb_oem:                   db 'MSWIN4.1'         ;  8 bytes
bpb_bytes_per_sector:      dw 512                ;  2 bytes
bpb_sectors_per_cluster:   db 1                  ;  1 byte
bpb_reserved_sectors:      dw 1                  ;  2 bytes
bpb_fat_count:             db 2                  ;  1 byte
bpb_dir_entries_count:     dw 0E0h               ;  2 bytes
bpb_total_sectors:         dw 2880               ;  2 bytes
bpb_media_descriptor_type: db 0F0h               ;  1 byte
bpb_sectors_per_fat:       dw 9                  ;  2 bytes
bpb_sectors_per_track:     dw 18                 ;  2 bytes
bpb_heads:                 dw 2                  ;  2 bytes
bpb_hidden_sectors:        dd 0                  ;  4 bytes
bpb_large_sector_count:    dd 0                  ;  4 bytes

;ebr
ebr_drive_number:          db 0                  ;  1 byte
ebr_windows_flags:         db 0                  ;  1 byte 
ebr_signature:             db 28h                ;  1 byte
ebr_volume_SN:             dd 12346578h          ;  4 bytes
ebr_volume_label:          db 'BedOS      '      ; 11 bytes
ebr_fat_identifier:        db 'FAT12   '         ;  2 bytes

start:
    ; setup data segments
    mov ax, 0
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7C00

    cli

    push es
    push word .after
    retf
.after:
    mov si, msg_loading
    call print

    ; read from floppy
    mov [ebr_drive_number], dl

    ; read drive parameters
    push es
    mov ah, 08h
    int 13h
    jc floppy_error
    pop es

    and cl, 0x3F
    xor ch, ch
    mov [bpb_sectors_per_track], cx

    inc dh
    mov [bpb_heads], dh

    ; read FAT root directory
    mov ax, [bpb_sectors_per_fat]
    mov bl, [bpb_fat_count]
    xor bh, bh
    mul bx
    add ax, [bpb_reserved_sectors]
    push ax

    mov ax, [bpb_sectors_per_fat]
    shl ax, 5
    xor dx, dx
    div word [bpb_bytes_per_sector]

    test dx, dx
    jz .root_dir_after
    inc ax

.root_dir_after:

    mov cl, al
    pop ax
    mov dl, [ebr_drive_number]
    mov bx, buffer
    call read_disk

    ; search for kernel.bin
    xor bx, bx
    mov di, buffer

.search_kernel:
    mov si, next_stage_file_name
    mov cx, 11
    push di
    repe cmpsb
    pop di
    je .found_kernel

    add di, 32
    inc bx
    cmp bx, [bpb_dir_entries_count]
    jl .search_kernel

    jmp kernel_not_found

.found_kernel:

    mov ax, [di + 26]
    mov [next_stage_cluster], ax

    mov ax, [bpb_reserved_sectors]
    mov bx, buffer
    mov cl, [bpb_sectors_per_fat]
    mov dl, [ebr_drive_number]
    call read_disk

    mov bx, NEXT_STAGE_LOAD_SEGMENT
    mov es, bx
    mov bx, NEXT_STAGE_LOAD_OFFSET

.load_kernel_loop:
    mov ax, [next_stage_cluster]

    add ax, 31                  ;TODO

    mov cl, 1
    mov dl, [ebr_drive_number]
    call read_disk

    add bx, [bpb_bytes_per_sector]

    mov ax, [next_stage_cluster]
    mov cx, 3
    mul cx
    mov cx, 2

    div cx

    mov si, buffer
    add si, ax
    mov ax, [ds:si]

    or dx, dx
    jz .even
.odd:
    shr ax, 4
    jmp .next_cluster_after
.even:
    and ax, 0x0FF
.next_cluster_after:
    cmp ax, 0x0FF
    jae .read_finish

    mov [next_stage_cluster], ax
    jmp .load_kernel_loop

.read_finish:
    mov dl, [ebr_drive_number]
    mov ax, NEXT_STAGE_LOAD_SEGMENT
    mov ds, ax
    mov es, ax

    jmp NEXT_STAGE_LOAD_SEGMENT:NEXT_STAGE_LOAD_OFFSET

    jmp wait_for_key_and_reboot

    hlt

.halt:
    cli
    jmp .halt
    hlt

; Converts an LBA address to a CHS address
; Parameters:
;   - ax: LBA address
; Returns:
;   - cx [bits 0-5]: sector number
;   - cx [bits 6-15]: cylinder
;   - dh: head
;
lba_2_chs:
    push ax
    push dx
    xor dx, dx                       ; dx = 0
    div word [bpb_sectors_per_track] ; ax = LBA / SectorsPerTrack
                                     ; dx = LBA % SectorsPerTrack
    inc dx                           ; dx = LBA % SectorsPerTrack + 1 = sector
    mov cx, dx

    xor dx, dx                       ; dx = 0
    div word [bpb_heads]             ; ax = (LBA / SectorsPerTrack) / Heads = cylinder
                                     ; dx = (LBA / SectorsPerTrack) % Heads = head
    
    mov dh, dl                       ; dh = head
    mov ch, al                       ; ch = cylinder (8 lower bits)
    shl ah, 6
    or cl, ah                        ; set 2 upper bits

    pop ax
    mov dl, al
    pop ax
    ret

; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx: memory address where to store read data
;
read_disk:
    push ax
    push bx
    push dx
    push di

    push cx
    call lba_2_chs
    pop ax

    mov ah, 02h
    mov di, 3

.retry:
    pusha
    stc

    int 13h
    jnc .done

    ; failed
    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    ; can't read floppy
    jmp floppy_error


.done:
    popa
    pop di
    pop dx
    pop bx
    pop ax
    ret

;
; Resets disk controller
; Parameters:
;   dl: drive number
;
disk_reset:
    pusha
    mov ah, 0
    stc
    int 13h
    jc floppy_error
    popa
    ret

floppy_error:
    mov si, msg_floppy_read_error
    call print
    jmp wait_for_key_and_reboot

kernel_not_found:
    mov si, msg_kernel_not_found
    call print
    jmp wait_for_key_and_reboot

wait_for_key_and_reboot:
    mov ah, 0
    int 16h
    jmp 0FFFFh:0


;
; Prints string to the screen
; Parameters
;   si: string address
print:
    push si
    push ax
    push bx

.loop:
    lodsb
    or al, al
    jz .done

    mov ah, 0x0E
    mov bh, 0
    pusha
    int 0x10
    popa
    jmp .loop

.done:
    pop bx
    pop ax
    pop si
    ret

msg_loading:            db 'Loading kernel...', ENDL, 0
msg_floppy_read_error:  db 'Floppy error!', ENDL, 0
msg_kernel_not_found:   db 'kernel.bin file not found!', ENDL, 0

next_stage_file_name:       db 'BOOT    BIN'
next_stage_cluster:         db 0

NEXT_STAGE_LOAD_SEGMENT:    equ 0x2000
NEXT_STAGE_LOAD_OFFSET:     equ 0

times 510 - ($ - $$) db 0
dw 0xAA55
buffer: