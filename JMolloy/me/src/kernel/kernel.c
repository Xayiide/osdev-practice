#include <stdint.h>
#include "lib/sys.h"
#include "drivers/vga.h"
#include "mm/pmm.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/irq.h"
#include "cpu/pit.h"
#include "drivers/kb.h"
#include "multiboot.h"

extern struct multiboot_header mbheader __attribute__((section(".multiboot")));

void kmain(multiboot_info_t *mbd, uint32_t magic)
{
    /* Initialize terminal interface */
    vga_init();
    printk("Bienvenido a ChamacOS\n");

    gdt_init();
    printk("GDT inicializado\n");

    idt_init();
    printk("IDT inicializado\n");

    isr_init();
    printk("ISRs inicializados\n");

    irq_init();
    printk("IRQs inicializados\n");

    pmm_init(mbd, magic);

    sti();

    pit_install_handler();
    printk("Timer instalado\n");

    kb_install_handler();
    printk("Teclado instalado\n");

    printk("mbh magic:         0x%x\n", mbheader.magic);
    printk("mbh header_addr:   0x%x\n", mbheader.header_addr);
    printk("mbh load_addr:     0x%x\n", mbheader.load_addr);
    printk("mbh load end addr: 0x%x\n", mbheader.load_end_addr);
    printk("mbh bss_end addr:  0x%x\n", mbheader.bss_end_addr);


}

