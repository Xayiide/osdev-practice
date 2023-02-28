BUILD_DIR = ../../build/os/mem

MEM_SRCS  = $(wildcard *.c)
MEM_OBJS  = $(patsubst %.c, $(BUILD_DIR)/%.o, $(MEM_SRCS))

CC    = i686-elf-gcc

FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-used-function -fno-builtin -Werror -Wno-cpp   \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

.PHONY: all clean re


all: $(MEM_OBJS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(FLAGS) -std=gnu99 -c $< -o $@

clean:
	rm -f $(MEM_OBJS)

re: clean all
