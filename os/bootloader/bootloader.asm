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

    mov si, msg_hello
    call print

    hlt

.halt:
    cli
    jmp .halt

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

msg_hello: db 'Hello World!', ENDL, 0