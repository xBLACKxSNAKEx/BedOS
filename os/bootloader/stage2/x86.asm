bits 16

section _TEXT class=CODE

global _x86_Video_WriteChar
_x86_Video_WriteChar:
    ; make new call frame
    push bp             ; save old call frame
    mov bp, sp          ; init new call frame

    ; save bx
    push bx

    mov ah, 0Eh
    mov al, [bp + 4]
    mov bh, [bp + 6]

    int 10h

    ; restore bx
    pop bx
    
    ; restore old call frame
    mov sp, bp
    pop bp
    ; return from function
    ret
