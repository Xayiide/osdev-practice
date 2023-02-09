; boot.asm
org 0
bits 16

_start:
    jmp short start
    nop

times 33 db 0 ; 33 octetos cero (Bios Parameter Block)


start:
    jmp 0x7c0:step2; code segment en 0x7c0

handle_int_zero:
    mov ah, 0eh
    mov al, 'A'  ; vamos a imprimir A
    mov bx, 0x00
    int 0x10
    iret

handle_int_one:
    mov ah, 0eh
    mov al, 'B'
    mov bx, 0x00
    int 0x10
    iret

step2:
    cli ; desactiva las interrupciones
    mov ax, 0x7c0 ; No podemos moverlo de una a DS ni a ES
    mov ds, ax
    mov es, ax
    ; stack segment
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00

    sti ; activa las interrupciones de vuelta

    ; interrupt table empieza en la dirección 0x0 de RAM
    mov word[ss:0x00], handle_int_zero ; mueve la dir de handle_int_zero
                                       ; a la pos. 0x00 de Stack Segment
    mov word[ss:0x02], 0x7c0

    mov word[ss:0x04], handle_int_one
    mov word[ss:0x06], 0x7c0

    int 1
    mov ax, 0x00
    div ax ; division por cero: int 0

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

