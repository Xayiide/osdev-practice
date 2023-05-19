#include <stddef.h>      /* size_t */
#include <stdint.h>      /* uint_t */

#include "sys.h"
#include "drivers/vga.h" /* printk */

static uint32_t    uptime_seconds = 0;

/* TODO: mover a string.h */
void *memcpy(void *dest, const void *src, size_t n)
{
    const char *sp;
    char *dp;

    sp = (const char *) src;
    dp = (char *) dest;

    for (; n != 0; n--)
        *dp++ = *sp++;

    return dest;
}

/* TODO: mover a string.h */
void *memset(void *dest, uint8_t byte, size_t n)
{
    uint8_t *temp;

    temp = (uint8_t *) dest;

    for (; n != 0; n--)
        *temp++ = byte;

    return dest;
}

/* TODO: mover a string.h */
void *memsetw(void *dest, uint16_t val, size_t n)
{
    uint16_t *temp;

    temp = (uint16_t *) dest;

    for (; n != 0; n--)
        *temp++ = val;

    return dest;
}

/* TODO: mover a string.h */
size_t strlen(const char *s)
{
    size_t ret;

    for (ret = 0; *s != '\0'; s++)
        ret++;

    return ret;
}

char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*dest++ = *src++));
    return d;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';

    return dest;
}



void sys_uptime_add_sec()
{
    uptime_seconds++;
}

uint32_t sys_uptime()
{
    return uptime_seconds;
}


void cli()
{
    __asm__ volatile("cli");
}

void sti()
{
    __asm__ volatile("sti");
}

/* TODO: mover a math.h? */
char *changebase(uint32_t num, base_t base)
{
    static char repr[] = "0123456789ABCDEF";
    static char buff[50];

    char *ptr;

    ptr  = &buff[49];
    *ptr = '\0';

    do
    {
        *--ptr = repr[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
}

__attribute__((noreturn)) void panic(const char *str)
{
    vga_color(VGA_BACK_BLACK, VGA_FORE_RED);
    printk("Kernel panic: %s\n", str);
    vga_color(VGA_BACK_BLACK, VGA_FORE_WHITE);
    for (;;);
}
