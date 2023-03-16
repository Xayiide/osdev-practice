#include "idt.h"
#include "isr.h"
#include "mem/mem.h"  /* memset       */
#include "gdt/gdt.h"  /* GDT macros   */
#include "kernel.h"   /* print        */

extern void idt_load(idtr_t *); /* idt.asm */

extern void        *isr_stub_table[];
extern void        *irq_stub_table[];
static idt_entry_t  idt[IDT_MAX_DESCRIPTORS];
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

    for (vector = IDT_NUM_EXCEPTIONS; vector < IRQ_NUM_INTERRUPTS; vector++) {
        idt_set(vector, irq_stub_table[vector], IDT_R0_X32_INT);
    }

    idt_load(&idtr);
}

void idt_en_ints() {
    __asm__ volatile ("sti; ret");
}

void idt_dis_ints() {
    __asm__ volatile ("cli; ret");
}

void isr_exception_handler(isr_frame_t *ifr) {
    uint32_t int_num, err_num;
    print("Ha ocurrido una excepcion: ");

    int_num = ifr->fr.intno;
    err_num = ifr->fr.errno;

    if (err_num == 0) {} else {}

    /* En lugar de un switch hacer un array de punteros a funciones para poder
     * hacer algo en plan int_functions[ifr->fr.intno].handle() o algo
     */
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
    case 5:
        print("5\n");
        break;
    case 6:
        print("6\n");
        break;
    case 7:
        print("7\n");
        break;
    case 8:
        print("8\n");
        break;
    case 9:
        print("9\n");
        break;
    case 10:
        print("10\n");
        break;
    case 11:
        print("11\n");
        break;
    case 12:
        print("12\n");
        break;
    case 13:
        print("13\n");
        break;
    default:
        print("Other\n");
        break;
    }

    //__asm__ volatile("cli; hlt");
}

void irq_interrupt_handler(uint32_t irq, uint32_t isr) {
    print("Ha ocurrido un irq\n");

    if (isr == 33)
        print("Teclado\n");

    if (irq == 1)
        print("IRQTECLADO\n");
}