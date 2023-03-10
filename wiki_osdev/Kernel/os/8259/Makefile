BUILD_DIR = ../../build/os/8259
INCLUDE   = -I../

PIC_SRCS = pic.c
PIC_OBJS = $(BUILD_DIR)/pic.o

CC = i686-elf-gcc
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels      \
		-falign-loops -fstrength-reduce -fomit-frame-pointer                  \
		-finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-cpp \
		-Wno-unused-label -Wno-unused-parameter -nostdlib -nostartfiles -Wall \
		-nodefaultlibs -O0

.PHONY: all clean re

all: $(PIC_OBJS)

$(BUILD_DIR)/pic.o: pic.c
	$(CC) $(FLAGS) $(INCLUDE) -std=gnu99 -c $< -o $@

clean:
	rm -f $(PIC_OBJS)

re: clean all
