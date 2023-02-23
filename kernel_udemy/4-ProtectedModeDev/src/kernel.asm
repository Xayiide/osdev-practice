[BITS 32]

global _start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp ; podemos acceder a mas memoria

    ; Enable A20 (from osdev wiki page)
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Remap the master PIC
    mov al, 00010001b ; Modo inicializacion
    out 0x20, al      ; Master PIC

    mov al, 0x20      ; Interrupt 0x20 -> donde el master ISR empieza
    out 0x21, al

    mov al, 00000001b ; Modo x86_64
    out 0x21, al

    ; Enable interrupts
    ; sti ; This is dangerous because the interrupt descriptor table
          ; is not yet initialized
    
    call kernel_main
    jmp $

times 512-($ - $$) db 0 ; alineamiento con código C
