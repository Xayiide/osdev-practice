FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

FILES = kernel.asm.o kernel.o

all: boot.bin kernel.bin
	@rm -f disk.img
	dd if=boot.bin >> disk.img
	dd if=kernel.bin >> disk.img
	dd if=/dev/zero bs=512 count=100 >> disk.img

kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o kernelfull.o
	i686-elf-gcc $(FLAGS) -T linker.ld -o kernel.bin -ffreestanding -O0 -nostdlib kernelfull.o

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

kernel.asm.o: kernel.asm
	nasm -f elf -g kernel.asm -o kernel.asm.o

kernel.o: kernel.c
	i686-elf-gcc $(FLAGS) -std=gnu99 -c kernel.c -o kernel.o


qemu:
	qemu-system-i386 -hda disk.img -gdb tcp::26000 -S

clean:
	rm -f disk.img boot.bin kernel.bin kernel.asm.o kernelfull.o kernel.o
