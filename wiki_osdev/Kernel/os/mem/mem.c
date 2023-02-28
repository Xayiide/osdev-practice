#include <stddef.h> /* size_t */

#include "mem.h"

void *memset(void *ptr, int c, size_t size) {
    int   i;
    char *c_ptr;

    c_ptr = (char *) ptr;
    for (i = 0; i < size; i++)
        c_ptr[i] = (char) c;

    return ptr;
}