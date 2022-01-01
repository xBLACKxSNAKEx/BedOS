org 0x7c00
bits 16

%define ENDL 0x0D, 0x0A

jmp start


start:
    hlt

.halt:
    cli
    jmp .halt