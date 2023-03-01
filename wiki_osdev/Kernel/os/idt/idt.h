#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h> /* uint */

typedef struct {
    uint16_t off1;   /* offset 1              */
    uint16_t segsel; /* selector de segmento  */
    uint8_t  zero;   /* sin uso. 0 siempre    */
    uint8_t  attr;   /* type, DPL, P (7 bits) */
    uint16_t off2;   /* offset 2              */
} __attribute__((packed)) idt_entry_t;

/* para el gdt se hacia en ensamblador, pero ahora ya podemos hacerlo en C */
typedef struct {
    uint16_t size;   /* Tamano IDT en bytes - 1              */
    uint32_t offset; /* Offset: dir. lineal de la tabla  IDT */
} __attribute__((packed)) idtr_t;

#endif
