# Para ejecutar este ejemplo
gdb
target remote | qemu-system-x86\_64 -hda boot.bin -S -gdb stdio
c
Ctrl-C
layout asm
info registers
