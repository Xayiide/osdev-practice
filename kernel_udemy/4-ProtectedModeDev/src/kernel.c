#include <stdint.h> /* uint16_t */
#include <stddef.h> /* size_t   */

#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"



void     terminal_initialize();
size_t   strlen(const char *str);
void     terminal_putchar(int, int, char, char);
uint16_t terminal_char_colour(char, char);
void     terminal_writechar(char, char);
void     print(const char *);






uint16_t *video_mem   = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;



uint16_t terminal_char_colour(char c, char colour) {
    return (colour << 8) | c;
}

void terminal_initialize() {
    int x, y;
    video_mem    = (uint16_t *) (0xB8000);
    terminal_col = 0;
    terminal_row = 0;

    for (y = 0; y < VGA_HEIGHT; y++) {
        for (x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }

}

void terminal_putchar(int x, int y, char c, char colour) {
    video_mem[(y * VGA_WIDTH + x)] = terminal_char_colour(c, colour);
}

size_t strlen(const char *str) {
    size_t len = 0;
    while(str[len])
        len++;

    return len;
}

void terminal_writechar(char c, char colour) {

    if (c == '\n') {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);   
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void print(const char *str) {
    int i;
    size_t len;

    len = strlen(str);
    for (i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
}

void kernel_main() {
    terminal_initialize();

    print("Hola, mundo.\nHola Cycarino:3");

    /* inicializa tabla de descriptores de interrupcion */
    idt_init();

    outb(0x60, 0xff);
}

