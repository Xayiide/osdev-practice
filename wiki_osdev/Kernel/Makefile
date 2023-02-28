export PREFIX=$(HOME)/opt/cross
export TARGET=i686-elf
export PATH := $(PREFIX)/bin:$(PATH)

BUILD_DIR = build
BOOT      = $(BUILD_DIR)/boot/boot.o
OS        = $(BUILD_DIR)/os/kernel.o
DISK_IMG  = disk.img
QEMU      = qemu-system-i386
QEMUOPTS  = -hda $(DISK_IMG) -gdb tcp::26000 -S


FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

.PHONY: all clean re qemu bootdisk boot os

all: bootdisk

bootdisk: boot os
	dd if=$(BOOT) of=$(DISK_IMG) bs=512 count=1
	dd if=$(OS) of=$(DISK_IMG) bs=512 seek=1
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=100 oflag=append conv=notrunc

boot:
	make -C boot

os:
	make -C os

qemu:
	$(QEMU) $(QEMUOPTS)

clean:
	make -C boot clean
	make -C os clean

re: clean all
