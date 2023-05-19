if grub-file --is-x86-multiboot kernel.bin; then
    echo Multiboot confirmado
else
    echo El binario no es Multiboot
fi
