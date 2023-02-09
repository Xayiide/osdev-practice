#include <stdio.h>

void preinit1() {
    printf("%s\n", __FUNCTION__);
}

void preinit2() {
    printf("%s\n", __FUNCTION__);
}

void init1() {
    printf("%s\n", __FUNCTION__);
}

void init2() {
    printf("%s\n", __FUNCTION__);
}

typedef void (*preinit)();
typedef void (*init)();

__attribute__((section(".preinit_array"))) preinit preinit_arr[2] = \
    {preinit1, preinit2};

__attribute__((section(".preinit_array"))) init init_arr[2] = \
    {init1, init2};


int main(int argc, char *argv[]) {
    printf("Hola, mundo\n");

    return 0;
}
