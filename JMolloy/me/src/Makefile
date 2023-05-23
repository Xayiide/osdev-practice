export PREFIX=$(HOME)/opt/cross
export TARGET=i686-elf
export PATH := $(PREFIX)/bin:$(PATH)

BUILD_DIR = ../build/
KERNEL_FULL = kernelfull.o

SRC_FILES = $(shell find -type f -name "*.c") \
			$(shell find -type f -name "*.asm")

DIR_FILES = $(patsubst ./%, $(BUILD_DIR)%, $(SRC_FILES))
FILES_1   = $(patsubst %.c, %.o, $(DIR_FILES))
FILES     = $(patsubst %.asm, %.o, $(FILES_1))

CC = i686-elf-gcc
LD = i686-elf-ld

CFLAG = -std=gnu99 -ffreestanding -Wall -Wextra -Werror
LFLAG = -Wl, --verbose

QEMU = qemu-system-i386
QOPT = -gdb tcp::26000 -S



.PHONY: all clean re fqemu cdqemu qemu

# NOTE: UFLAG se usa para llamar al comando make desde fuera:
# make fqemu UFLAG="-DDIAG"

all: $(KERNEL_FULL)
	$(CC) $(UFLAG) -T linker.ld -o kernel.bin -ffreestanding -nostdlib $(FILES) -lgcc
	@./scripts/is_multiboot.sh

$(KERNEL_FULL):
	make -C boot
	make -C cpu
	make -C lib
	make -C drivers
	make -C mm
	make -C task
	make -C kernel
	#$(LD) -g -relocatable $(FILES) -o ../build/kernelfull.o

clean:
	@echo find $(BUILD_DIR) -type f -name \"*.o\" -exec rm {} \\;
	$(shell find $(BUILD_DIR) -type f -name "*.o" -exec rm {} \;)
	rm -f kernel.bin kernel.iso

re: clean all

fqemu: re
	$(QEMU) -kernel kernel.bin

cdqemu: re
	mv kernel.bin ../isodir/boot/kernel.bin
	grub-mkrescue -o kernel.iso ../isodir
	$(QEMU) -cdrom kernel.iso
	
qemu: re
	$(QEMU) -kernel kernel.bin $(QOPT)
