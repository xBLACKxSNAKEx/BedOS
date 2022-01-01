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
ebr_volume_SN:             db 12h, 34h, 56h, 78h ;  4 bytes
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

    mov si, msg_loading
    call print

    hlt

.halt:
    cli
    jmp .halt

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

times 510 - ($ - $$) db 0
dw 0xAA55