global idt_load

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8] ; ebp+8 = primer argumento pasado como parametro
    lidt[ebx]          ; Carga el IDT
    sti                ; Activa las interrupciones?

    pop ebp
    ret