[ORG 0x7C00]
[BITS 16]

cli

mov ax, 0xb800
mov es, ax

mov si, mensaje
call print


hang:
    jmp hang


print:
.loop:
    lodsb
    cmp al, 0
    je .done
    call putchar
    jmp .loop
.done:
    add byte [ypos], 1  ; Baja una columna
    mov byte [xpos], 0  ; Ponte al principio
    ret

putchar:
    mov ah, 0Fh           ; Blanco sobre negro
    mov cx, ax            ; Guarda el char/atributo
    movzx ax, byte [ypos]
    mov dx, 160           ; 2 bytes char/atributo
    mul dx                ; 80 columnas
    movzx bx, byte [xpos]
    shl bx, 1             ; x2 para saltarse el atributo

    mov di, 0             ; inicio de memoria de video
    add di, ax            ; suma despl y
    add di, bx            ; suma despl x

    mov ax, cx            ; restaura char/atributo
    stosw                 ; escribe char/atributo
    add byte [xpos], 1    ; avanza a la dcha
    
    ret

mensaje db "ChamacOS!", 0
xpos    db 0
ypos    db 0


times 510 - ($-$$) db 0
dw 0xAA55
