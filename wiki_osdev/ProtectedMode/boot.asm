[ORG 0x7C00]
[BITS 16]

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

start:
    jmp .switch_prot



; Intel x86 SDM Vol3: 10.9.1
.switch_prot:
    cli                   ; Desactiva interrupciones
    lgdt [gdt_descriptor] ; Cargamos los 48 bits
                          ; Pon el bit PE en CR0 a 1
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp CODE_SEG:PModeMain
    

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
    mov eax, 1
    mov ebx, 2
    mov ecx, 3
    mov edx, 4
    jmp $

times 510 - ($-$$) db 0
dw 0xAA55
