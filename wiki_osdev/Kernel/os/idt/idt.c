#include "idt.h"
#include "mem/mem.h"  /* memset       */
#include "gdt/gdt.h"  /* GDT macros   */
#include "8259/pic.h" /* PIC_1_OFFSET */
#include "kernel.h"   /* print        */

extern void idt_load(idtr_t *); /* idt.asm */

extern void        *isr_stub_table[];
static idt_entry_t  idt[256];
static idtr_t       idtr;


void idt_set(int int_num, void *addr, uint8_t flags) {
    idt_entry_t *desc;
    desc        = &idt[int_num];
    desc->off1 = (uint32_t) addr & 0x0000FFFF;
    desc->ssel = GDT_OFFSET_KERNEL_CODE;
    desc->zero = 0;
    desc->attr = flags;
    desc->off2 = (uint32_t) addr >> 16;
}

void idt_init() {
    print("idt_init\n");
    uint8_t vector;
    memset(idt, 0, sizeof(idt));
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t) idt;

    for (vector = 0; vector < IDT_NUM_EXCEPTIONS; vector++) {
        idt_set(vector, isr_stub_table[vector], IDT_R0_X32_INT);
    }

    //idt_set(0, idt_div_zero_handler);
    //idt_set(PIC1_OFFSET + 0x01, isr_irq_01);
    idt_load(&idtr);
}

void idt_en_ints() {
    __asm__ volatile ("sti; ret");
}

void idt_dis_ints() {
    __asm__ volatile ("cli; ret");
}

void isr_exception_handler(int_frame *frame) {
    uint32_t int_num, err_num;
    print("Ha ocurrido una excepcion:");

    int_num = frame->intno;
    err_num = frame->errno;
    if (err_num == 0) {

    }
    else {

    }

    switch(int_num) {
    case 0:
        print("0\n");
        break;
    case 1:
        print("1\n");
        break;
    case 2:
        print("2\n");
        break;
    case 3:
        print("3\n");
        break;
    case 4:
        print("4\n");
        break;
    default:
        print("Other\n");
        break;
    }

    __asm__ volatile ("cli; hlt");
}