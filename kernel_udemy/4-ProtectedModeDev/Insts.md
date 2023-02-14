# Para ejecutar este ejemplo
gdb
target remote | qemu-system-x86\_64 -hda boot.bin -S -gdb stdio
c
Ctrl-C
layout asm
info registers

Deberíamos ver cómo bootea. En GDB, veríamos la dirección en la que estamos en 0x7c7f


# Para ejecutar el kernel con el driver ATA:
(desde bin/)
gdb
add-symbol-file ../build/kernelfull.o 0x100000
break \_start
target remote | qemu-system-x86\_64 -S -gdb stdio -hda ./os.bin
c

(\_start está en 0x100000)
layout asm
stepi (repite)
