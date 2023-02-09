#include <stdio.h>


__attribute__((destructor)) static void destructor() {
    printf("%s\n", __FUNCTION__);
}

int main(int argc, char *argv[]) {
    printf("Hola, mundo\n");

    return 0;
}

