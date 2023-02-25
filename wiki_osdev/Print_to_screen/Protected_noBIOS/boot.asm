[ORG 0x7C00]
[BITS 16]

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

start:
    jmp .switch_prot



; Intel x86 SDM Vol3: 10.9.1
.switch_prot:
    cli                   ; Desactiva interrupciones
    call enableA20        ; Activa linea A20
    lgdt [gdt_descriptor] ; Cargamos GDT - los 48 bits en GDTR


    ; Pon el bit PE en CR0 a 1 y salta al codigo de modo protegido
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp CODE_SEG:PModeMain
    

enableA20: ; wiki osdev
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; Intel x86 SDM Vol3: 3.4.5.
gdt_start:
gdt_null:          ; Segmento nulo
    dq 0h

gdt_code:
    dw 0xFFFF      ; Limite de seg. [0:15]
    dw 0           ; Dir. base [0:15]

    db 0           ; Dir. base [16:23]
    db 0x9A        ; Byte de acceso: P, DPL, S, Type
    db 11001111b   ; Byte de flags: G, DB, L, Reservado
    db 0           ; Dir. base [24:31]

gdt_data:
    dw 0xFFFF      ; Limite de seg. [0:15]
    dw 0           ; Dir. base [0:15]

    db 0           ; Dir. base [16:23]
    db 0x92        ; Byte de acceso: P, DPL, S, Type
    db 11001111b   ; Byte de flags: G, DB, L, Reservado
    db 0           ; Dir. base [24:31]

gdt_end:

; Intel x86 SDM Vol3: 2.4.1
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; 32b dir, base
    dd gdt_start               ; 16b limite de tabla

[BITS 32]
PModeMain:
    mov eax, 0
    mov ebx, 1
    mov ecx, 2
    mov edx, 3

    mov si, mensaje
    call print

hang:
    jmp hang


print:
    .loop:
    mov eax, [esi]     ; Estas dos instrucciones
    lea esi, [esi+1]   ;  sustituyen a lodsb
    cmp al, 0          ; Null-terminator?
    je .done           ;  si: terminamos
    call putchar       ;  no: imprimimos el siguiente
    jmp .loop          ; Volvemos a empezar
    .done:
    add byte [ypos], 1 ; Baja una columna
    mov byte [xpos], 0 ; Ponte al principio de la linea
    ret

putchar:
    mov ah, 0x0F
    mov ecx, eax
    movzx eax, byte [ypos]
    mov edx, 160
    mul edx
    movzx ebx, byte [xpos]
    shl ebx, 1

    mov edi, 0xb8000
    add edi, eax
    add edi, ebx

    mov eax, ecx
    mov word [ds:edi], ax
    add byte [xpos], 1 ; Avanza a la dcha

    ret

mensaje db "Bienvenido a ChamacOS!", 0
xpos    db 0
ypos    db 0

times 510 - ($-$$) db 0
dw 0xAA55
