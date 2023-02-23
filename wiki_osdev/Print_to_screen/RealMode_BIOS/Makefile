

all:
	nasm -f bin boot.asm -o boot.bin
	dd if=/dev/zero of=disk.img bs=512 count=2880
	dd if=boot.bin of=disk.img bs=512 count=1 seek=0

qemu: all
	qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000 -S

clean:
	rm -f disk.img boot.bin
