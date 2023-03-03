[BITS 32]

global _kstart  ; Sirve para linker.ld
global problem
extern kmain    ; Sirve por kernel.c

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_kstart:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x00200000
    mov esp, ebp        ; Acceder a mas memoria (??)

    call kmain

hang:
    jmp hang

times 512 - ($-$$) db 0