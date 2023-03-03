#ifndef _IO_H_
#define _IO_H_

unsigned char  insb(unsigned short port);
unsigned short insw(unsigned short port);
void outb(unsigned short port, unsigned char val); /* uint16_t, uint8_t */
void outw(unsigned short port, unsigned char val);

#endif