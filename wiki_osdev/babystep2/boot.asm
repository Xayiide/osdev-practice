ORG  0x7c00
bits 16

msg db 'Hello world', 0

start: jmp boot

boot:
    cli
    cld

    mov si, msg
    call print

print:
    mov bx, 0
.loop:
    lodsb         ; lo que hay en SI lo lleva a AH. Incrementa SI
    cmp al, 0     ; Fin del string
    jz .done
    call put
    jmp .loop
.done:
    ret

put:
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    ret


times 510 - ($-$$) db 0
db 0x55
db 0xAA
