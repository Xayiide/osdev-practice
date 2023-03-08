extern interrupt_handler

global idt_load
global isr_interrupt
global isr_stub_table

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8] ; ebp+8 = primer argumento pasado como parametro
    lidt [ebx]         ; Carga el IDT

    pop ebp
    ret

%macro isr_interrupt 1
isr_interrupt_%1:
    push dword %1
    call exception_handler
    iret
%endmacro



