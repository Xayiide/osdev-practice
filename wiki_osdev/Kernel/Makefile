export PREFIX=$(HOME)/opt/cross
export TARGET=i686-elf
export PATH := $(PREFIX)/bin:$(PATH)



FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

all:
	# boot.bin
	nasm -f bin boot.asm -o boot.bin
	# kernel.asm.o
	nasm -f elf -g kernel.asm -o kernel.asm.o
	# kernel.o
	i686-elf-gcc $(FLAGS) -std=gnu99 -c kernel.c -o kernel.o
	# kernelfull.o = kernel.asm.o + kernel.o
	i686-elf-ld -g -relocatable kernel.asm.o kernel.o -o kernelfull.o
	#kernel.bin = kernelfull.o + linker
	i686-elf-gcc $(FLAGS) -T linker.ld -o kernel.bin -ffreestanding -O0 -nostdlib kernelfull.o

	@rm -f disk.img
	dd if=boot.bin of=disk.img bs=512 count=1
	dd if=kernel.bin of=disk.img bs=512 seek=1
	dd if=/dev/zero of=disk.img bs=512 count=100 oflag=append conv=notrunc

qemu:
	qemu-system-i386 -hda disk.img -gdb tcp::26000 -S

clean:
	rm -f disk.img *.bin *.o
