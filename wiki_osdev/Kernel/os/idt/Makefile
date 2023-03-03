BUILD_DIR = ../../build/os/idt
INCLUDE   = -I../

IDT_SRCS = idt.c idt.asm
IDT_OBJS = $(BUILD_DIR)/idt.o $(BUILD_DIR)/idt.asm.o

CC  = i686-elf-gcc
AS  = nasm
ASF = -f elf

FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

.PHONY: all clean re

all: $(IDT_OBJS)

$(BUILD_DIR)/idt.o: idt.c
	$(CC) $(FLAGS) $(INCLUDE) -std=gnu99 -c $< -o $@

$(BUILD_DIR)/idt.asm.o: idt.asm
	$(AS) $(ASF) -g $< -o $@

clean:
	rm -f $(IDT_OBJS)

re: clean all