[BITS 32]

global _kstart  ; Sirve para linker.ld
extern kmain    ; Sirve por kernel.c

_kstart:
    ;mov ax, 0
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;mov ss, ax

    ;mov ebp, 0x00200000
    ;mov esp, ebp        ; Acceder a mas memoria (??)

    call kmain

hang:
    jmp hang

times 512 - ($-$$) db 0