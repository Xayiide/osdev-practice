#include "drivers/vga.h"
#include <stdint.h>

void kmain(uint32_t magic)
{
	/* Initialize terminal interface */
	vga_init();
    printk("Bienvenido a ChamacOS\n");
    printk("magic: 0x%x\n", magic);
}

