#include <stdio.h>

__attribute__ ((constructor(102))) static void init1() {
    printf("%s\n", __FUNCTION__);
}

__attribute__ ((constructor(101))) static void init2() {
    printf("%s\n", __FUNCTION__);
}

int main() {
    printf("Hola, mundo\n");

    return 0;
}

