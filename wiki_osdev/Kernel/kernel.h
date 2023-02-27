#ifndef _KERNEL_H_
#define _KERNEL_H_

#define VGA_ADDR 0xB8000
#define VGA_W      80
#define VGA_H      20

void kmain();
void print(const char *);


#endif