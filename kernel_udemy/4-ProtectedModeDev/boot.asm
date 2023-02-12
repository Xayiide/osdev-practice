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
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp ; podemos acceder a mas memoria
    jmp $

times 510-($ - $$) db 0
dw 0xAA55 ; little-endian
