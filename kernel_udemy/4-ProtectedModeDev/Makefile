FILES = ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/mem/mem.o ./build/io/io.asm.o ./build/mem/heap/heap.o ./build/mem/heap/kheap.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin
	@rm -f ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin # Sectores para el kernel 



./bin/kernel.bin: $(FILES)
	i686-elf-ld  -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o
	
./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o: ./src/idt/idt.c
	i686-elf-gcc $(INCLUDES) -I./src/idt $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/mem/mem.o: ./src/mem/mem.c
	i686-elf-gcc $(INCLUDES) -I./src/mem $(FLAGS) -std=gnu99 -c ./src/mem/mem.c -o ./build/mem/mem.o

./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

./build/mem/heap/heap.o: ./src/mem/heap/heap.c
	i686-elf-gcc $(INCLUDES) -I./src/mem/heap $(FLAGS) -std=gnu99 -c ./src/mem/heap/heap.c -o ./build/mem/heap/heap.o
	
./build/mem/heap/kheap.o: ./src/mem/heap/kheap.c
	i686-elf-gcc $(INCLUDES) -I./src/mem/heap $(FLAGS) -std=gnu99 -c ./src/mem/heap/kheap.c -o ./build/mem/heap/kheap.o


clean:
	rm -f ./bin/boot.bin
	rm -f ./bin/kernel.bin
	rm -f ./bin/os.bin
	rm -f $(FILES)
	rm -f ./build/kernelfull.o
