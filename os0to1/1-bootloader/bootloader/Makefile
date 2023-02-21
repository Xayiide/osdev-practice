BUILD_DIR=../build/bootloader

BOOTLOADER_SRCS := $(wildcard *.asm)
BOOTLOADER_OBJS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

AS      = nasm
ASFLAGS = -f bin

.PHONY: all clean re

all: $(BOOTLOADER_OBJS)

$(BUILD_DIR)/%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(BOOTLOADER_OBJS)

re: clean all
