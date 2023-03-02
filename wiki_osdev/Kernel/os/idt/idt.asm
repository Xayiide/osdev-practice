section .asm

idt_load:
    push ebp
    mov esp, ebp

    mov ebx, [ebp + 8]

    pop ebp
    ret