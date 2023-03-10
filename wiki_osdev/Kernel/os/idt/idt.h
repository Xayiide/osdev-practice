#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h> /* uint */

#define IDT_MAX_DESCRIPTORS 256
#define IDT_NUM_EXCEPTIONS  32

#define IDT_GATE_TASK     0x05
#define IDT_GATE_X16_INT  0x06
#define IDT_GATE_X16_TRAP 0x07
#define IDT_GATE_X32_INT  0x0E
#define IDT_GATE_X32_TRAP 0x0F

#define IDT_GATE_PRES     0x80 // 1000
#define IDT_GATE_R0       0x00 // 0000 -> Por defecto al usar GATE_PRESENT
#define IDT_GATE_R1       0x40 // 0100
#define IDT_GATE_R2       0x20 // 0010
#define IDT_GATE_R3       0x60 // 0110

#define IDT_R0_X32_INT  (IDT_GATE_PRES | IDT_GATE_X32_INT)  // 8Eh
#define IDT_R0_X32_TRAP (IDT_GATE_PRES | IDT_GATE_X32_TRAP) // 8Fh
#define IDT_R3_X32_INT  (IDT_GATE_PRES | IDT_GATE_R3 | IDT_GATE_X32_INT) // EEh
#define IDT_R3_X32_TRAP (IDT_GATE_PRES | IDT_GATE_R3 | IDT_GATE_X32_TRAP) //EFh

typedef struct {
    uint16_t off1; /* offset 1                 */
    uint16_t ssel; /* selector de segmento     */
    uint8_t  zero; /* sin uso. 0 siempre       */
    uint8_t  attr; /* type, S, DPL, P (8 bits) */
    uint16_t off2; /* offset 2                 */
} __attribute__((packed)) idt_entry_t;

/* para el gdt se hacia en ensamblador, pero ahora ya podemos hacerlo en C */
typedef struct {
    uint16_t limit; /* Tamano IDT en bytes - 1              */
    uint32_t base;  /* Offset: dir. lineal de la tabla  IDT */
} __attribute__((packed)) idtr_t;

void idt_init();
void idt_en_ints();
void idt_dis_ints();


#endif
