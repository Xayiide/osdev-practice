AS   = nasm
ASFL = -f bin

.PHONY: all clean re qemu

TGT = bootloader
SRC = bootloader.asm
DSK = disk.img

all: $(TGT)

$(TGT): $(SRC)
	$(AS) $(ASFL) $^ -o $@
	dd if=/dev/zero of=$(DSK) bs=512 count=2880
	dd conv=notrunc if=$(TGT) of=$(DSK) bs=512 count=1 seek=0

qemu: $(TGT)
	qemu-system-i386 -machine q35 -fda $(DSK) -gdb tcp:26000 -S


clean:
	@rm -f $(TGT) $(DSK)

re: clean all
