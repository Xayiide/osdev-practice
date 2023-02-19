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

# Para ejecutar el kernel con el driver de io:
gdb
add-symbol-file ../build/kernelfull.o 0x100000
target remote | qemu-system-x86\_64 -S -gdb stdio -hda ./os.bin
break kernel.c:92 (la linea del outb 0x60 0xff)
c
layout asm
stepi

Ahora continuamos hasta que entramos en la función outb. Avanzamos con stepi
hasta la instrucción out. Ahí vemos el estado de los registros:  
print $eax (debería ser 255 = 0xff)
print $edx (debería ser 96 = 0x60)


# Para ejecutar el manejador de IDT de presiones de teclado
desde bin
qemu-system-x86\_64 -hda ./os.bin

Sólo muestra el mensaje una vez.
