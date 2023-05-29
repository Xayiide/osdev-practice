BITS 32

;                   MULTIBOOT
MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
MAGIC    equ 0x1BADB002
FLAGS    equ MBALIGN | MEMINFO
CHECKSUM equ -(MAGIC + FLAGS)


GLOBAL mbheader
extern code         ; linker.ld
extern bss          ;
extern end          ;

section .multiboot
align 4
mbheader:           ; kernel.c
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    dd mbheader
    dd code
    dd bss
    dd end
    dd _start

global _kstack_end
global _kstack_start
section .bss
align 16
_kstack_end: ; stack bottom
    resb 16384
_kstack_start: ; stack top


section .text
extern kmain
global _start
_start:
    mov esp, _kstack_start ; Hacemos un stack
    push eax               ; multiboot magic
    push ebx               ; multiboot info structure
    call kmain

    jmp $

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                   GDT - Vol3: 3.4.5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global gdt_load
extern gdtr         ; gdt.c - Vol3: 2.4.1
gdt_load:
    lgdt[gdtr]      ; Carga el GDT con la variable gdtr de gdt.c
    mov ax, 0x10    ; 0x10 es el despl. de nuestro segmento de datos en el GDT

    mov ds, ax      ; Inicializa los registros de segmento
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush2 ; 0x08 es el despl. del segmento de código - far jump
flush2:
    ret             ; Retorna al código de C

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                   ISRs
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global idt_load
global isr_vector

extern idtr              ; idt.c
extern isr_fault_handler ; isr.c

idt_load:           ; Vol3: 6.10
    lidt[idtr]
    ret

%macro isr_err_stub 1
isr_stub_%+%1:
    cli
    push byte %1    ; Apilo no. de interrupt. El no. de error ya lo apila la CPU
    jmp isr_common_stub
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    cli
    push byte 0     ; Apilo no. de error de mentira (Vol3: 6.12)
    push byte %1    ; Apilo no. de interrupción
    jmp isr_common_stub
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
    pushad
    push ds         ; Guarda registros de segmento
    push es
    push fs
    push gs

    mov ax, 0x10    ; Segmento de datos del kernel
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push eax
    mov eax, isr_fault_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popad

isr_vector:
%assign i 0
%rep 32
    dd isr_stub_%+i
%assign i i+1
%endrep

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; IRQs (PIC)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
extern irq_fault_handler ; irq.c
global irq_vector        ; irq.c

%macro irq_stub 1
irq_stub_%+%1:
    cli
    push byte 0
    push byte %1
    jmp irq_common_stub
%endmacro

irq_stub 32
irq_stub 33
irq_stub 34
irq_stub 35
irq_stub 36
irq_stub 37
irq_stub 38
irq_stub 39
irq_stub 40
irq_stub 41
irq_stub 42
irq_stub 43
irq_stub 44
irq_stub 45
irq_stub 46
irq_stub 47

irq_common_stub:
    pushad
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push eax
    mov eax, irq_fault_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popad

    add esp, 8
    iret

irq_vector:
%assign i 32
%rep 16
    dd irq_stub_%+i
%assign i i+1
%endrep

section .text
global switchTask
switchTask:
    pusha
    pushf
    mov eax, cr3
    push eax
    mov eax, [esp + 44] ; First argument, where to save
    mov [eax + 4],  ebx
    mov [eax + 8],  ecx
    mov [eax + 12], edx
    mov [eax + 16], esi
    mov [eax + 20], edi
    mov ebx, [esp + 36] ; EAX
    mov ecx, [esp + 40] ; EIP
    mov edx, [esp + 20] ; ESP
    add edx, 4          ; Remove the return value
    mov esi, [esp + 16] ; EBP
    mov edi, [esp + 4]  ; EFLAGS
    mov [eax], ebx
    mov [eax + 24], edx
    mov [eax + 28], esi
    mov [eax + 32], ecx
    mov [eax + 36], edi
    pop ebx             ; CR3?
    mov [eax + 40], ebx
    push ebx            ; Goodbye again
    mov eax, [esp + 48] ; New object
    mov ebx, [eax + 4]  ; EBX
    mov ecx, [eax + 8]  ; ECX
    mov edx, [eax + 12] ; EDX
    mov esi, [eax + 16] ; ESI
    mov edi, [eax + 20] ; EDI
    mov ebp, [eax + 28] ; EBP
    push eax
    mov eax, [eax + 36] ; EFLAGS
    push eax
    popf
    pop eax
    mov esp, [eax + 24] ; ESP
    push eax
    mov eax, [eax + 40] ; CR3
    mov cr3, eax
    pop eax
    push eax
    mov eax, [eax + 32] ; EIP
    xchg [esp], eax
    mov eax, [eax]      ; EAX
    ret
