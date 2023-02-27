FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0


all:
	nasm -f bin boot.asm -o boot.bin # boot.bin
	nasm -f elf -g kernel.asm -o kernel.asm.o # kernel.asm.o
	i686-elf-gcc $(FLAGS) -std=gnu99 -c kernel.c -o kernel.o # kernel.o
	i686-elf-ld -g -relocatable kernel.asm.o kernel.o -o kernelfull.o
	i686-elf-gcc $(FLAGS) -T linker.ld kernelfull.o -o kernel.bin
	
	dd if=boot.bin of=disk.img bs=512 count=1
	dd if=kernel.bin of=disk.img bs=512 count=1 seek=1
	dd if=/dev/zero of=disk.img bs=512 count=100 seek=2

qemu:
	qemu-system-i386 -hda disk.img -gdb tcp::26000 -S

clean:
	rm -f disk.img boot.bin kernel.bin kernel.asm.o kernelfull.o kernel.o
