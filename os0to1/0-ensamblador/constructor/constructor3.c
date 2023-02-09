#include <stdio.h>

void init1() {
    printf("%s\n", __FUNCTION__);
}

void init2() {
    printf("%s\n", __FUNCTION__);
}

typedef void (*init)();

__attribute__((section(".init_array"))) init init_arr[2] = {init1, init2};

int main(int argc, char *argv[]) {
    printf("Hola, mundo\n");

    return 0;
}
