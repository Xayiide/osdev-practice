# Instrucciones
Construimos con `make qemu`.  
Entramos en gdb, ponemos la arquitectura en i8086 y display para asm y
registros.  
Continuamos y Ctrl-C. Vemos que estamos en el jmp y que los registros
están puestos bien.

# Instrucciones
Si se hace `make disk-qemu`, se arranca desde disco hd y no desde floppy.
Es extraño pero en este modo, si pongo `-machine q35` pasan cosas raras
durante el arranque.
