; boot.asm
org 0
bits 16

_start:
    jmp short start
    nop

times 33 db 0 ; 33 octetos cero (Bios Parameter Block)

start:
    jmp 0x7c0:step2; code segment en 0x7c0

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

    ; Preparamos para leer el sector 2 del disco
    mov ah, 2 ; comando para leer un sector
    mov al, 1 ; leemos un sector
    mov ch, 0 ; octeto bajo del cilindro
    mov cl, 2 ; numero de sector
    mov dh, 0 ; cabezal
    ; no ponemos dl porque la BIOS lo hace por nosotros.

    mov bx, buffer
    int 0x13 ;int 13h

    jc error ; if carry flag: error

    mov si, buffer
    call print

    jmp $

error:
    mov si, error_msg
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
    
error_msg: db "Error al cargar el sector", 0

times 510-($ - $$) db 0
dw 0xAA55 ; little-endian


buffer: ; etiqueta sin nada
; aunque pusiéramos algo como
; buffer: db 'hola'
; nunca se cargaría, porque la BIOS sólo carga un único sector y
; en esta altura ya hemos pasado los 512 bytes (times 510- etc etc)
; Sin embargo sí que podemos referenciarlo aunque no se vaya a cargar
; por eso nos resulta útil poner la etiqueta de buffer aquí
