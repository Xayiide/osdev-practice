set architecture i8086
add-symbol-file build/os/kernelfull.o 0x100000
set disassembly-flavor intel
target remote localhost:26000
layout asm
layout regs
