#include <stdint.h>
#include "lib/sys.h"
#include "drivers/vga.h"
#include "multiboot.h"

extern struct multiboot_header mbheader __attribute__((section(".multiboot")));

void kmain(multiboot_info_t *mbd, uint32_t magic)
{
	/* Initialize terminal interface */
	vga_init();
    printk("Bienvenido a ChamacOS\n");
    printk("magic: 0x%x\n", magic);

    multiboot_info_t *ejemplo = mbd;
    ejemplo++; ejemplo--;

    printk("mbh magic:         0x%x\n", mbheader.magic);
    printk("mbh header_addr:   0x%x\n", mbheader.header_addr);
    printk("mbh load_addr:     0x%x\n", mbheader.load_addr);
    printk("mbh load end addr: 0x%x\n", mbheader.load_end_addr);
    printk("mbh bss_end addr:  0x%x\n", mbheader.bss_end_addr);


}

