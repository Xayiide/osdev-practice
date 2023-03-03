#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h> /* uint_t */

struct idt_desc {
    uint16_t offset_1; /* despl bits 0-15 */
    uint16_t selector; /* selector en nuestro GDT */
    uint8_t zero;      /* sin usar */
    uint8_t type_attr; /* tipo y atributos de la tabla */
    uint16_t offset_2; /* despl bits 16-31 */
} __attribute__((packed));


struct idtr_desc {
    uint16_t limit; /* tamanio de la tabla - 1 */
    uint32_t base;  /* dir base del comienzo de la tabla */
} __attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();

#endif