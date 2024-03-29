#include <stddef.h> /* size_t */
#include <stdint.h> /* uint   */

#include "kernel.h"

#include "idt/idt.h"  /* idt_init */
#include "8259/pic.h" /* pic      */

static void     term_printc(char c, char color);
static size_t   strlen(const char *str);
static void     term_init();
static void     term_putc(int x, int y, char c, char color);
static uint16_t term_color(char c, char color);

static uint16_t *video_mem = 0;
static uint16_t  term_row  = 0;
static uint16_t  term_col  = 0;

extern void divzero();

void kmain()
{
    term_init();
    print("ChamacOS!\n");

    idt_init();
    print("^^^^^^^^^\n");
    pic_remap(PIC1_OFFSET, PIC1_OFFSET + 0x08);
    idt_en_ints();
    print("=========");
    //divzero();
    while (1);
}

void print(const char *str)
{
    int    i;
    size_t len;

    len = strlen(str);
    for (i = 0; i < len; i++)
    {
        term_printc(str[i], 15); /* black */
    }
}

static void term_printc(char c, char color)
{
    if (c == '\n')
    {
        term_row += 1;
        term_col  = 0;
    }
    else
    {
        term_putc(term_col, term_row, c, color);
        term_col += 1;
        if (term_col >= VGA_W)
        {
            term_row += 1;
            term_col  = 0;
        }
    }
}

static size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

static void term_init()
{
    int x, y;
    video_mem = (uint16_t *) (VGA_ADDR);
    term_row  = 0;
    term_col  = 0;

    for (y = 0; y < VGA_H; y++)
    {
        for (x = 0; x < VGA_W; x++)
        {
            term_putc(x, y, ' ', 0); /* espacios negros */
        }
    }
}

static void term_putc(int x, int y, char c, char color)
{
    video_mem[(y * VGA_W + x)] = term_color(c, color);
}

static uint16_t term_color(char c, char color)
{
    uint16_t col;
    col = (color << 8) | c;

    return col;
}