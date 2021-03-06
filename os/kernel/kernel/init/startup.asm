[bits 16]

%define ENDL 0x0D, 0x0A

jmp start
nop
g_GDT:
    ; NULL
    dw 0x0000
    dw 0x0000
    db 0x00
    db 0b00000000
    db 0b00000000
    db 0x00

    ; 32-bit code segment
    dw 0xFFFF                   ; limit (bits 0-15) = 0xFFFFF for full 32-bit range
    dw 0x0000                   ; base (bits 0-15) = 0x0
    db 0x00                     ; base (bits 16-23)
    db 0b10011010               ; access (present, ring 0, code segment, executable, direction 0, readable)
    db 0b11001111               ; granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
    db 0x00                     ; base high

    ; 32-bit data segment
    dw 0xFFFF                   ; limit (bits 0-15) = 0xFFFFF for full 32-bit range
    dw 0x0000                   ; base (bits 0-15) = 0x0
    db 0x00                     ; base (bits 16-23)
    db 0b10010010               ; access (present, ring 0, data segment, executable, direction 0, writable)
    db 0b11001111               ; granularity (4k pages, 32-bit pmode) + limit (bits 16-19)
    db 0x00                     ; base high

g_GDTD:
    dw g_GDTD - g_GDT - 1
    dd g_GDT

start:
    cli
    call get_memory_map
    call A20_check
    test ax, 0
    jnz .next
    call A20_enable
    .next:
    lgdt [g_GDTD]

    mov ebx, cr0
    or ebx, 1
    mov cr0, ebx
    
    jmp 08h:pmode
    hlt

; Function: A20_enable
;
; Purpose: enable A20 line in keyboard controller
;
; Returns: nothing

A20_enable:
    push ax
    ; disable keyboard
    call A20_wait_out
    mov al, 0xAD
    out 0x64, al

    ; command for reading
    call A20_wait_out
    mov al, 0xD0
    out 0x64, al

    ; read from input
    call A20_wait_in
    in al, 0x60
    push ax

    ; command for writing 
    call A20_wait_out
    mov al, 0xD1
    out 0x64, al

    ; write to output
    call A20_wait_out
    pop ax
    or al, 2
    out 0x60, al

    ; enable keyboard
    call A20_wait_out
    mov al, 0xAE
    out 0x64, al

    call A20_wait_out
    pop ax
    ret

A20_wait_out:
    in      al,0x64
    test    al,2
    jnz     A20_wait_out
    ret

A20_wait_in:
    in      al,0x64
    test    al,1
    jz     A20_wait_in
    ret

; Function: A20_check
;
; Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
;          The function can be modified as necessary by removing push's at the beginning and their
;          respective pop's at the end if complete self-containment is not required.
;
; Returns: 0 in ax if the a20 line is disabled (memory wraps around)
;          1 in ax if the a20 line is enabled (memory does not wrap around)
 
A20_check:
    pushf
    push ds
    push es
    push di
    push si
 
    xor ax, ax ; ax = 0
    mov es, ax
 
    not ax ; ax = 0xFFFF
    mov ds, ax
 
    mov di, 0x0500
    mov si, 0x0510
 
    mov al, byte [es:di]
    push ax
 
    mov al, byte [ds:si]
    push ax
 
    mov byte [es:di], 0x00
    mov byte [ds:si], 0xFF
 
    cmp byte [es:di], 0xFF
 
    pop ax
    mov byte [ds:si], al
 
    pop ax
    mov byte [es:di], al
 
    mov ax, 0
    je .A20_check__exit
 
    mov ax, 1
 
.A20_check__exit:
    pop si
    pop di
    pop es
    pop ds
    popf
 
    ret

; TODO: get memory map from BIOS
global get_memory_map
get_memory_map:
;    memory_map_address
    pusha
    push ax
    push bx
    push cx
    push es
    push di
    push ebp
    mov eax, 0
    mov es, eax
    mov di, memory_map_address
    xor ebx, ebx
    xor ebp, ebp
    .loop:
    mov edx, 0x534D4150
    mov eax, 0xE820
    mov [es:di + 20], dword 1
    mov ecx, 24
    int 15h
    jc .done     ; error

    or ebx, ebx  ; no more entries
    jz .done

    or ecx, ecx  ; returned length is 0
    jz .loop

    add di, 24
    inc ebp

    jmp .loop
    .done:
    mov [0x500], ebp
    pop ebp
    pop di
    pop es
    pop cx
    pop bx
    pop ax
    popa
    ret

pmode:
[bits 32]

    extern kernel_early_main
    call kernel_early_main

    hlt

memory_map_count_address: equ 0x500
memory_map_address:       equ 0x501