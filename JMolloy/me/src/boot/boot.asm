BITS 32

MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
MAGIC    equ 0x1BADB002
FLAGS    equ MBALIGN | MEMINFO
CHECKSUM equ -(MAGIC + FLAGS)


GLOBAL mbheader
extern code
extern bss
extern end

section .multiboot
align 4
mbheader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    dd mbheader
    dd code
    dd bss
    dd end
    dd _start

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:


section .text
extern kmain
global _start
_start:
    mov esp, stack_top
    push eax ; multiboot magic
    push ebx ; multiboot heder location
    call kmain

    cli
.1:
    hlt
    jmp 1
