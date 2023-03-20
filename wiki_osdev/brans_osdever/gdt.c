#include "system.h"

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char  base_middle;
    unsigned char  access;
    unsigned char  granularity;
    unsigned char  base_high;
} __attribute__((packed));


struct gdt_ptr
{
    unsigned short limit;
    unsigned char  base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* function in start.asm */
extern void gdt_flush();


void gdt_set_gate(int num, unsigned long base, unsigned long limit, \
                  unsigned char access, unsigned char gran)
{
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0x0F);
    gdt[num].access      = access;
}

void gdt_install()
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base  = &gdt;

    gdt_set_gate(0, 0, 0, 0, 0); /* NULL descriptor */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Data Segment */

    gdt_flush();
}
