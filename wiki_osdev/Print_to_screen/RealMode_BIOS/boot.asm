[ORG 0x7C00]
[BITS 16]

cli             ; Desactiva interrupciones
mov si, mensaje ; pon el mensaje en SI
call print      ; imprime el mensje

hang:
    jmp hang

print:
    mov bh, 0
    mov bl, 0
.loop:
    lodsb          ; Carga SI en AH, incrementa SI
    cmp al, 0      ; null-terminator?
    je .done       ;  hemos llegado al final del string
    call putchar   ; no hemos terminado
    jmp .loop
.done:
    ret


putchar:
    mov ah, 0eh ; video - teletype output
    int 10h
    ret

mensaje: db "ChamacOS", 0

times 510 - ($-$$) db 0
dw 0xAA55
