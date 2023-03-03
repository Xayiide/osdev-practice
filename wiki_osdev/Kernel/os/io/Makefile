BUILD_DIR = ../../build/os/io
INCLUDE   = -I../

IO_SRCS = io.asm
IO_OBJS = $(BUILD_DIR)/io.asm.o

AS  = nasm
ASF = -f elf

.PHONY: all clean re

all: $(IO_OBJS)

$(BUILD_DIR)/io.asm.o: io.asm
	$(AS) $(ASF) -g $< -o $@

clean:
	rm -f $(IO_OBJS)

re: clean all