[ORG 0x7C00]
[BITS 16]

CODE_SEG equ gdt_code - gdt_start ; despl de gdt_code (0x8)
DATA_SEG equ gdt_data - gdt_start ; despl de gdt_data (0x10)

start:
    jmp .switch_prot

; Intel x86 SDM Vol3: 10.9.1
.switch_prot:
    cli                   ; Desactiva interrupciones

    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

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
    dw gdt_end - gdt_start - 1 ; 32b dir, base. Tamano del descriptor
    dd gdt_start               ; 16b limite de tabla. Offset del descriptor.

; Aqui ya no estamos en modo real, no podemos usar servicios de la BIOS
[BITS 32]
PModeMain:
    ; Cargar siguientes sectores de disco, donde va a estar contenido el kernel
    mov eax, 1             ; Primer sector que cargamos (0 = bootloader)
    mov ecx, 100           ; Cargamos 100 sectores
    mov edi, 0x0100000      ; Los cargamos en la pos. 0x0100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000 ; Saltamos a donde acabamos de cargarlos

ata_lba_read:
    mov ebx, eax           ; Guarda el LBA

    mov edx, 0x01F6    ; Puerto al que enviar bits 24-27 de LBA
    shr eax, 24        ; Pon los bits 24-27 en AL
    or  eax, 11100000b ; Pon bit 6 en AL para modo LBA
    out  dx, al

    mov edx, 0x1F2     ; Puerto al que enviar numero de sectores
    mov eax, ecx       ; Ponemos en EAX el numero
    out  dx, al

    mov edx, 0x1F3     ; Puerto al que enviar bits 0-7 de LBA
    mov eax, ebx       ; Restaura LBA
    out  dx, al

    mov edx, 0x1F4     ; Puerto al que enviar bits 8-15 de LBA
    mov eax, ebx       ; Restaura LBA
    shr eax, 8         ; Pon los bits 8-15 en AL
    out  dx, al

    mov edx, 0x1F5     ; Puerto al que enviar bits 16-23 de LBA
    mov eax, ebx       ; Restaura LBA
    shr eax, 16        ; Pon los bits 16-23 en AL
    out  dx, al

    mov edx, 0x1F7     ; Puerto de comando
    mov al, 0x20       ; Lee con reintento
    out dx, al

.next_sector:
    push ecx

.try_again:
    mov edx, 0x1F7
    in   al, dx        ; Lee del puerto 0x1F7
    test al, 8         ; mascara
    jz .try_again      ; bucle

    mov ecx, 256       ; Lee 512 bytes
    mov edx, 0x1F0
    rep insw           ; Lee una palabra del puerto 1F0 y la guarda en DS
    pop ecx            ; Restaura ECX
    loop .next_sector
    ret


times 510 - ($-$$) db 0
dw 0xAA55
