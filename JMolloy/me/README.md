# IMPORTANTE
Tenía este mismo problema:  
https://forum.osdev.org/viewtopic.php?f=1&t=28835&start=0  

· `qemu-system-i386 -cdrom myos.iso` me daba error de arranque, pero  
· `qemu-system-i386 -kernel myos.bin` me funcionaba  

Hay que:
`sudo apt install grub-pc-bin` por algún motivo

