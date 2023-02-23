# /bin/bash

nasm -f bin boot.asm -o boot.bin
dd if=/dev/zero of=disk.img bs=512 count=2880
dd conv=notrunc if=boot.bin of=disk.img bs=512 count=1 seek=0
