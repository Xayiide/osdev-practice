global idt_load


idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt [ebx]

    pop ebp
    ret



extern isr_exception_handler
global isr_stub_table

%macro isr_err_stub 1
isr_stub_%+%1:
    push %1 ; No apila el no. de error porque la CPU lo hace automaticamente
    call isr_common_stub
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push 0xDEFECADA  ; Apila un "no. de error" de mentira (Vol3: 6.12)
    push %1
    call isr_common_stub
    iret
%endmacro


 ; Volume 3: 6.3.1 (table 6-1)
isr_no_err_stub 0  ; Divide error
isr_no_err_stub 1  ; Debug exception
isr_no_err_stub 2  ; NMI interrupt
isr_no_err_stub 3  ; Breakpoint
isr_no_err_stub 4  ; Overflow
isr_no_err_stub 5  ; BOUND range exceeded
isr_no_err_stub 6  ; Invalid opcode (undefined opcode)
isr_no_err_stub 7  ; Device not available (no math coprocessor)
isr_err_stub    8  ; Double Fault
isr_no_err_stub 9  ; Coprocessor segment overrun (reserved)
isr_err_stub    10 ; Invalid TSS
isr_err_stub    11 ; Segment not present
isr_err_stub    12 ; Stack-segment fault
isr_err_stub    13 ; General Protection
isr_err_stub    14 ; Page Fault
isr_no_err_stub 15   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 16 ; x87 FPU Floating-point Error (Math fault)
isr_err_stub    17 ; Alignment check
isr_no_err_stub 18 ; Machine check
isr_no_err_stub 19 ; SIMD Floating-point Exception
isr_no_err_stub 20 ; Virtualization exception
isr_no_err_stub 21 ; Control Protection exception
isr_no_err_stub 22   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 23   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 24   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 25   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 26   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 27   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 28   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 29   ; INTEL RESERVED DO NOT USE
isr_err_stub    30   ; INTEL RESERVED DO NOT USE
isr_no_err_stub 31   ; INTEL RESERVED DO NOT USE
                     ; 32-255 User defined

isr_common_stub:
    cli

    ; [44] eflags 
    ; [40] cs
    ; [36] eip
    ; [32] no. error (apilado por nosotros en los isrs que no lo generan)
    ; [28] no. int. (apilado siempre por nosotros) ; ESP apunta aqui al entrar
    ; [24] eip isr_stub_%i
    ;pushad ; Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI

    push ebp
    mov ebp, esp


    mov eax, [ebp+12] ; TODO: hacer el pushad para mantener bien todo el estado
    mov ebx, [ebp+8]

    push eax ; err_no
    push ebx ; int_no ; Estas dos lineas montan el struct (al reves)
    push esp ; Esta linea apila el ESP: manda el puntero al struct
    call isr_exception_handler ; (int_no, err_no)

    ;add esp, 8 ; restaura el ESP 

    mov esp, ebp
    pop ebp      ; Restaura el EBP

    sti
    iret


isr_stub_table:
%assign i 0
%rep 32
    dd isr_stub_%+i
%assign i i+1
%endrep
