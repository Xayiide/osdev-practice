#include <stdint.h>  /* uint_t */
#include "kernel.h"
#include "idt.h"
#include "config.h"
#include "mem/mem.h"


struct idt_desc  idt_descriptors[CHAMACOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc *ptr);

void idt_zero() {
    print("Divide by zero error\n");
}

void idt_set(int intnum, void *address) {
    struct idt_desc* desc = &idt_descriptors[intnum];
    desc->offset_1  = (uint32_t) address & 0x0000FFFF; /* parte baja */
    desc->selector  = KERNEL_CODE_SELECTOR;
    desc->zero      = 0x00;
    desc->type_attr = 0xEE; /* P,DPL,S y Tipo. Por eso no es solo 0E sino EE */
    desc->offset_2  = (uint32_t) address >> 16; /* parte alta */
}


void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base  = (uint32_t) idt_descriptors;

    idt_set(32, idt_zero);

    idt_load(&idtr_descriptor);
}
