BUILD_DIR=../build/os

OS_SRCS := $(wildcard *.asm)
OS_OBJS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(OS_SRCS))

AS      = nasm
ASFLAGS = -f bin

all: $(OS_OBJS)

$(BUILD_DIR)/%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@


clean:
	rm -f $(OS_OBJS)

re: clean all
