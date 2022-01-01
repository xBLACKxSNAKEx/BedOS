org 0
bits 16

%define ENDL 0x0D, 0x0A

start:
    mov ah, 0
    int 16h
    mov si, msg_kernel
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

msg_kernel: db 'Welcome to stage2', ENDL, 0