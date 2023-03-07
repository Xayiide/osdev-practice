#ifndef _ISR_H_
#define _ISR_H_

#define IRQ_TIMER    0
#define IRQ_KEYBOARD 1
#define IRQ_CASCADE  2   /* Not used */
#define IRQ_COM2     3
#define IRQ_COM1     4
#define IRQ_LPT2     5
#define IRQ_FLOPPY   6
#define IRQ_LPT1     7   /* Spurious          */
#define IRQ_RTCLK    8   /* Real Time Clock   */
#define IRQ_FREE1    9   /* Legacy SCSI / NIC */
#define IRQ_FREE2    10  /* SCSI / NIC        */
#define IRQ_FREE3    11  /* SCSI / NIC        */
#define IRQ_PS2MOUSE 12
#define IRQ_FPU_PROC 13  /* FPU - CoProcessor */
#define IRQ_ATA1     14  /* Primary ATA       */
#define IRQ_ATA2     15  /* Secondary ATA     */

void null_int_handler();
void div_zero_handler();

void irq_00_handler();
void irq_01_handler();


#endif