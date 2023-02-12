AS   = nasm
ASFL = -f bin


.PHONY: all clean re qemu disk

TGT = boot.bin
SRC = boot.asm
TXT = msg.txt

all: $(TGT)

$(TGT): $(SRC)
	$(AS) $(ASFL) $^ -o $@

disk: $(TGT)
	dd if=$(TXT) >> $(TGT)
	dd if=/dev/zero bs=512 count=1 >> $(TGT) # Rellena con 0s el sector

qemu: $(TGT)
	qemu-system-x86_64 -hda $^

clean:
	@rm -f $(TGT)

re: clean all

