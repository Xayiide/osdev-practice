#include <stdint.h> /* uint   */
#include "io/io.h"  /* in out */
#include "pic.h"

void pic_remap(uint8_t off1, uint8_t off2) {
    uint8_t master_mask, slave_mask;

    /* Guarda las mascaras de cada PIC. Sin CMD mandado, DAT devuelve la
     * mascara actual.
     * https://wiki.osdev.org/PIC#Masking
    */
    master_mask = inb(PIC1_DAT);
    slave_mask  = inb(PIC2_DAT);

    /* Comienza la secuencia de inicializacion */
    outb(PIC1_CMD, PIC_ICW1_INIT);
    outb(PIC2_CMD, PIC_ICW1_INIT);

    /* Manda ICW2: El despl del vector */
    outb(PIC1_DAT, off1);
    outb(PIC2_DAT, off2);

    /* Manda ICW3: El cableado de cada PIC */
    outb(PIC1_DAT, 4); /* PIC2 en IRQ2 (0000 0100) */
    outb(PIC2_DAT, 2); /* PIC1 en IRQ9 creo, no entiendo por que el 2 */

    /* Manda ICW4: Modo 8086 */
    outb(PIC1_DAT, PIC_ICW4_8086);
    outb(PIC2_DAT, PIC_ICW4_8086);

    /* Restaura las mascaras de cada PIC */
    outb(PIC1_DAT, master_mask);
    outb(PIC2_DAT, slave_mask);
}

void pic_set_mask(uint8_t irq) {
    uint16_t port;
    uint8_t  val;

    if (irq < 8) {
        port = PIC1_DAT;
    }
    else {
        port = PIC2_DAT;
        irq -= 8;
    }

    val = inb(port) | (1 << irq);
    outb(port, val);
}

void pic_clr_mask(uint8_t irq) {
    uint16_t port;
    uint8_t  val;

    if (irq < 8) {
        port = PIC1_DAT;
    }
    else {
        port = PIC2_DAT;
        irq -= 8;
    }
    
    val = inb(port) & ~(1 << irq);
    outb(port, val);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_CMD, PIC_EOI);
    else
        outb(PIC1_CMD, PIC_EOI);
}

void pic_disable() {
    uint8_t i;
    uint8_t off1 = 0x20; /* por defecto */

    pic_remap(off1, off1 + 0x08);

    for (i = 0; i < 16; i++) {
        pic_set_mask(i);
    }
}