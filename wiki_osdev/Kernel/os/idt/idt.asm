extern null_int_handler
extern div_zero_handler
extern irq_00_handler
extern irq_01_handler

global isr_null_int
global isr_div_zero
global isr_irq_00
global isr_irq_01

global idt_load

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8] ; ebp+8 = primer argumento pasado como parametro
    lidt[ebx]          ; Carga el IDT

    pop ebp
    ret

isr_div_zero:
    cli
    cld    ; SYS-V ABI
    pushad

    call div_zero_handler

    popad
    sti
    iret

isr_null_int:
    cli
    cld
    pushad

    call null_int_handler

    popad
    sti
    iret

isr_irq_00:
    cli
    cld
    pushad

    call irq_00_handler

    popad
    sti
    iret

isr_irq_01:
    cli
    cld
    pushad

    call irq_01_handler

    popad
    sti
    iret