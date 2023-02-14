; boot.asm
org 0x7c00
bits 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


_start:
    jmp short start
    nop

times 33 db 0 ; 33 octetos cero (Bios Parameter Block)

start:
    jmp 0:step2; code segment en 0x7c0

step2:
    cli ; desactiva las interrupciones
    mov ax, 0x00 ; No podemos moverlo de una a DS ni a ES
    mov ds, ax
    mov es, ax
    ; stack segment
    mov ss, ax
    mov sp, 0x7c00
    sti ; activa las interrupciones de vuelta

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, CR0
    or eax, 0x1
    mov CR0, eax
    jmp CODE_SEG:load32

; Global Descriptor Table GDT
gdt_start:
gdt_null: ; GDT Null descriptor
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:     ; CS should point to this
    dw 0xFFFF ; Segment limit 0-15 bits
    dw 0      ; Base first 0-15 bits
    db 0      ; Base 16-23 bits
    db 0x9a   ; Access byte
    db 11001111b ; high 4 bit flags and low 4 bits flags
    db 0      ; Base 24-31 bits

; offset 0x10
gdt_data:        ; DS, SS, ES, FS, GS
    dw 0xFFFF    ; Segment limit 0-15 bits
    dw 0         ; Base first 0-15 bits
    db 0         ; Base 16-23 bits
    db 0x92      ; Access byte
    db 11001111b ; high 4 bit flags and low 4 bits flags
    db 0         ; Base 24-31 bits
    
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start

[BITS 32]
load32:
    ; 32 bit mode
    ; load our kernel into memory and jump to it
    mov eax, 1   ; primer sector desde el que cargamos (0 es boot)
    mov ecx, 100 ; cargamos 100 sectores
    mov edi, 0x0100000 ; dirección de comienzo (donde vamos a cargarlos)
    call ata_lba_read  ; driver de disco para cargar sectores en memoria
    jmp CODE_SEG:0x0100000

ata_lba_read:
    mov ebx, eax ; backup LBA
    ; enviar los 8 bits mas altos de lba al controlador de disco
    shr eax, 24 ; despl. dcha 24 bits para quedarse con los 8 altos
    or eax, 0xE0 ; Select the master drive
    mov dx, 0x1F6
    out dx, al ; Envia los 8 bits mas altos de lba

    mov eax, ecx
    mov dx, 0x1F2
    out dx, al ; Envia el total de sectores a leer

    mov eax, ebx ; restaura el LBA
    mov dx, 0x1F3
    out dx, al

    mov dx, 0x1F4
    mov eax, ebx ; restaura el LBA de backup
    shr eax, 8
    out dx, al ; Termina de enviar mas bits de LBA

    ; Enviar los 16 bits mas altos de LBA
    mov dx, 0x1F5
    mov eax, ebx ; restaura LBA
    shr eax, 16
    out dx, al

    mov dx, 0x1F7
    mov al, 0x20
    out dx, al

    ; Read all sectors into memory
.next_sector:
    push ecx

; Comprueba si necesitamos leer
.try_again:
    mov dx, 0x1F7
    in al, dx ; lee del puerto 0x1F7
    test al, 8 ; máscara
    jz .try_again ; bucle


    ; lee 256 palabras de una vez (1 sector)
    mov ecx, 256
    mov dx, 0x1F0
    rep insw ; lee una palabra del puerto 0x1F0 y guardala en 0x010000 (ds)
    pop ecx ; restaura ecx (del push en .next_sector)
    loop .next_sector
    ret


times 510-($ - $$) db 0
dw 0xAA55 ; little-endian
