AS   = nasm
ASFL = -f bin


.PHONY: all clean re qemu

TGT = boot.bin
SRC = boot.asm

all: $(TGT)

$(TGT): $(SRC)
	$(AS) $(ASFL) $^ -o $@

qemu: $(TGT)
	qemu-system-x86_64 -hda $^

clean:
	@rm -f $(TGT)

re: clean all

