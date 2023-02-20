#ifndef _KHEAP_H_
#define _KHEAP_H_

#include <stddef.h>

void  kheap_init();
void *kmalloc(size_t size);
void  kfree(void *ptr);

#endif
