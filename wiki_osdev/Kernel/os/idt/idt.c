#include "idt.h"
#include "mem/mem.h" /* memset     */
#include "gdt/gdt.h" /* GDT macros */
#include "kernel.h"  /* print      */

extern void idt_load(idtr_t *); /* idt.asm */


static idt_entry_t idt[256];
static idtr_t      idtr;

void idt_zero() {
    print("Divide by zero error\n");
}

void idt_set(int int_num, void *addr) {
    idt_entry_t *desc;
    desc        = &idt[int_num];
    desc->off1 = (uint32_t) addr & 0x0000FFFF;
    desc->ssel = GDT_OFFSET_KERNEL_CODE;
    desc->zero = 0;
    desc->attr = IDT_R3_X32_INT; // EE
    desc->off2 = (uint32_t) addr >> 16;
}

void idt_init() {
    memset(idt, 0, sizeof(idt));
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t) idt;

    idt_set(0, idt_zero);
    idt_load(&idtr);
}

void idt_en_ints() {
    __asm__ volatile ("sti; ret");
}

void idt_dis_ints() {
    __asm__ volatile ("cli; ret");
}