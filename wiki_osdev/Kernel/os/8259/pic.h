#ifndef _PIC_H_
#define _PIC_H_

#define PIC1          0x20 /* Master PIC */
#define PIC1_CMD      PIC1
#define PIC1_DAT      0x21

#define PIC2          0xA0 /* Slave PIC */
#define PIC2_CMD      PIC2
#define PIC2_DAT      0xA1

#define PIC_ICW1_ICW4 0x01
#define PIC_ICW1_INIT 0x10
#define PIC_EOI       0x20 /* End of Interrupt */

#endif