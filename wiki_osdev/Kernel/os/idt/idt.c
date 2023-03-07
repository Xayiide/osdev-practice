#include "isr.h"
#include "idt.h"
#include "mem/mem.h"  /* memset       */
#include "gdt/gdt.h"  /* GDT macros   */
#include "8259/pic.h" /* PIC_1_OFFSET */
#include "kernel.h"   /* print        */

extern void idt_load(idtr_t *); /* idt.asm */

extern void isr_null_int();     /* isr.asm */
extern void isr_div_zero();     /* isr.asm */
extern void isr_irq_00();       /* isr.asm */
extern void isr_irq_01();       /* isr.asm */


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
    //uint8_t i;

    memset(idt, 0, sizeof(idt));
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t) idt;

    //for (i = 0; i < IDT_MAX_DESCRIPTORS; i++) {
    //    idt_set(i, isr_null_int);
    //}

    idt_set(0, isr_div_zero);
    idt_set(PIC1_OFFSET + 0x01, isr_irq_01);
    idt_load(&idtr);
}

void idt_en_ints() {
    __asm__ volatile ("sti; ret");
}

void idt_dis_ints() {
    __asm__ volatile ("cli; ret");
}



void null_int_handler() {
    return;
}
void div_zero_handler() {
    print("Division por zero prohibida\n");
    return;
}

void irq_00_handler() {
    return;
}
void irq_01_handler() {
    print("Tecla presionada\n");
    pic_send_eoi(IRQ_KEYBOARD);
}

