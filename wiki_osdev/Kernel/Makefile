FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0


all:
	# boot.bin
	nasm -f bin boot.asm -o boot.bin
	# kernel.asm.o
	nasm -f elf -g kernel.asm -o kernel.asm.o # kernel.asm.o
	# kernel.o
	i686-elf-gcc $(FLAGS) -std=gnu99 -c kernel.c -o kernel.o # kernel.o
	# kernel.asm.o + kernel.o = kernelfull.o
	i686-elf-ld -g -relocatable kernel.asm.o kernel.o -o kernelfull.o
	# kernelfull.o + linker = kernel.bin
	i686-elf-gcc $(FLAGS) -T linker.ld kernelfull.o -o kernel.bin
	
	rm -f disk.img
	# 1 sector de bootloader
	dd if=boot.bin >> disk.img
	# n sectores de kernel
	dd if=kernel.bin >> disk.img
	# 10 sectores vacíos
	dd if=/dev/zero bs=512 count=100 > disk.img

qemu:
	qemu-system-i386 -hda disk.img -gdb tcp::26000 -S

clean:
	rm -f disk.img boot.bin kernel.bin kernel.asm.o kernelfull.o kernel.o
