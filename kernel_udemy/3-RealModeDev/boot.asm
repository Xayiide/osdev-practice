; boot.asm
org 0
bits 16

start:
    cli ; desactiva las interrupciones
    mov ax, 0x7c0 ; No podemos moverlo de una a DS ni a ES
    mov ds, ax
    mov es, ax

    ; stack segment
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00

    sti ; activa las interrupciones de vuelta
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
    

msg: db "Hola, cargabotas", 0

times 510-($ - $$) db 0
dw 0xAA55 ; little-endian

