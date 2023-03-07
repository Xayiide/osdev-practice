#ifndef _PIC_H_
#define _PIC_H_

#include <stdint.h> /* uint */

#define PIC1          0x20 /* Master PIC */
#define PIC1_CMD      PIC1
#define PIC1_DAT      0x21

#define PIC2          0xA0 /* Slave PIC */
#define PIC2_CMD      PIC2
#define PIC2_DAT      0xA1

#define PIC_ICW1_INIT 0x11
#define PIC_ICW4_8086 0x01 /* Modo 8086/88         */
#define PIC_ICW4_AUTO 0x02 /* Modo auto EOI        */
#define PIC_ICW4_BUFS 0x08 /* Buffered mode slave  */
#define PIC_ICW4_BUFM 0x0C /* Buffered mode master */
#define PIC_ICW4_SFN  0x10 /* Special Fully Nested */

#define PIC_EOI       0x20 /* End of Interrupt     */

void pic_send_eoi(uint8_t irq);
void pic_remap(uint8_t off1, uint8_t off2);
void pic_disable();
void pic_set_mask(uint8_t irq);
void pic_clr_mask(uint8_t irq);

#endif