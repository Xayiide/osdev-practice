BOOTLOADER = bootloader.o
OS         = sample.o
DISK_IMG   = disk.img
QEMU       = qemu-system-i386
QEMU_OPTS  = -machine q35 -fda $(DISK_IMG) -gdb tcp::26000 -S

.phony: all clean re qemu

BOOTLOADER_SRCS := $(wildcard *.asm)
BOOTLOADER_OBJS := $(patsubst %.asm, %.o, $(BOOTLOADER_SRCS))

all: bootdisk

%.o: %.asm
	nasm -f bin $< -o $@

bootdisk: $(BOOTLOADER_OBJS)
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	dd conv=notrunc if=$(BOOTLOADER) of=$(DISK_IMG) bs=512 count=1 seek=0
	dd conv=notrunc if=$(OS) of=$(DISK_IMG) bs=512 count=1 seek=1


clean:
	rm -f $(BOOTLOADER_OBJS) $(OS) $(DISK_IMG)


re: clean all

qemu: all
	$(QEMU) $(QEMU_OPTS)
