ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K)
    {
        code = .; /* multiboot_header */
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        bss = .; /* multiboot_header */
        *(COMMON)
        *(.bss)
    }
    end = .; /* multiboot_header */

    /* Otras secciones producidas por el compilador */
}

