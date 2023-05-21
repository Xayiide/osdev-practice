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

    printk("mbh magic:         0x%x\n", mbheader.magic);
    printk("mbh header_addr:   0x%x\n", mbheader.header_addr);
    printk("mbh load_addr:     0x%x\n", mbheader.load_addr);
    printk("mbh load end addr: 0x%x\n", mbheader.load_end_addr);
    printk("mbh bss_end addr:  0x%x\n", mbheader.bss_end_addr);


    uint32_t i;
    multiboot_memory_map_t *mmt;

    for (i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t))
    {
        mmt = (multiboot_memory_map_t *) (mbd->mmap_addr + i);
        if (mmt->type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            vga_color(VGA_BACK_BLACK, VGA_FORE_CYAN);
            printk("Memoria usable: ");
            printk(" [0x%x -> 0x%x] (%d KBs)\n", mmt->addr_lo,
                    (mmt->addr_lo + mmt->len_lo), mmt->len_lo/1024);
        }
    }

}

