BUILD_DIR =../build/os
LK_SCRIPT = linker.ld

# TODO: encontrar una forma mas bonita de hacer esto
KERNEL_ASM_O = $(BUILD_DIR)/kernel.asm.o
KERNEL_BIN   = $(BUILD_DIR)/kernel.bin
KERNELFULL_O = $(BUILD_DIR)/kernelfull.o
KERNEL_O     = $(BUILD_DIR)/kernel.o
MEM_O        = $(BUILD_DIR)/mem/mem.o
IDT_O        = $(BUILD_DIR)/idt/idt.o $(BUILD_DIR)/idt/idt.asm.o
IO_O         = $(BUILD_DIR)/io/io.asm.o # Hay que incluir esto
PIC_O        = $(BUILD_DIR)/8259/pic.o



FILES        = $(KERNEL_ASM_O) $(KERNEL_BIN) $(MEM_O) $(IDT_O) $(PIC_O)
OS_OBJS      = $(FILES) $(KERNELFULL_O) $(KERNEL_O)

AS  = nasm
ASF = -f elf
CC  = i686-elf-gcc
LD  = i686-elf-ld

CFLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		 -falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		 -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-cpp \
		 -Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		 -nodefaultlibs -O0

.PHONY: all clean re

all: $(KERNEL_O)


# 1. kernel.asm -> kernel.asm.o
$(KERNEL_ASM_O): kernel.asm
	$(AS) $(ASF) -g $^ -o $@

# 2. kernel.c -> kernel.bin
$(KERNEL_BIN): kernel.c
	$(CC) $(CFLAGS) -std=gnu99 -c $^ -o $@

# 3. kernel.asm.o + kernel.o -> kernelfull.o
$(KERNELFULL_O): $(FILES)
	$(LD) -g -relocatable $(FILES) -o $@

# 4. kernelfull.o + linker = kernel.o
$(KERNEL_O): $(KERNELFULL_O)
	$(CC) $(CFLAGS) -T $(LK_SCRIPT) $^ -o $@

$(MEM_O):
	make -C mem

$(PIC_O):
	make -C 8259

$(IDT_O):
	make -C idt

#$(IO_O):
#	make -C io


clean:
	rm -f $(OS_OBJS)

re: clean all
