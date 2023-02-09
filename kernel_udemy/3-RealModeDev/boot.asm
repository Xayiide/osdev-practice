; boot.asm
org 0x7c00
bits 16

start:
    mov si, msg ; la direccion de la etiqueta 'msg' a si
    call print
    jmp $ ; bucle infinito (documentacion nasm)

print:
    mov bx, 0
.loop:
    lodsb ; carga el caracter de si a ah e incrementa si
    cmp al, 0 ; null-terminator
    je .done
    call putchar
    jmp .loop

.done:
    ret
    

putchar:
    mov ah, 0eh ; Command (video - teletype output)
    int 0x10    ; Rutina de BIOS
    ret
    

msg: db "Hola Nano, come caca", 0

times 510-($ - $$) db 0
dw 0xAA55 ; little-endian

