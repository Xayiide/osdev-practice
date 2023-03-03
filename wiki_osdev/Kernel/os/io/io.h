#ifndef _IO_H_
#define _IO_H_

#include <stdint.h> /* uint */

/* OUT DX, AL : Se envía al puerto en DX el byte que hay en AL */
inline __attribute__((always_inline))
void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a" (val), "Nd" (port));
    /* a:  Fuerza que val sea puesto en EAX antes de que se ejecute la inst.
     * Nd: Permite que las ctes de 1 byte sean ensambladas como ctes y así
           liberar el registro EDX */
}

inline __attribute__((always_inline))
void outw(uint16_t port, uint16_t val) {
    __asm__ volatile("outw %0, %1" : : "a" (val), "Nd" (port));
}

inline __attribute__((always_inline))
void outl(uint16_t port, uint32_t val) {
    __asm__ volatile("outl %0, %1" : : "a" (val), "Nd" (port));
}

/* IN AL, DX : Se guarda un byte en AL del puerto en DX */
inline __attribute__((always_inline))
uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : : "a" (ret), "Nd" (port));
    return ret;
}

inline __attribute__((always_inline))
uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ volatile("inw %1, %0" : : "a" (ret), "Nd" (port));
    return ret;
}

inline __attribute__((always_inline))
uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ volatile("inl %1, %0" : : "a" (ret), "Nd" (port));
    return ret;
}



#endif