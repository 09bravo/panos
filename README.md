# Overview
Panos is a lightweight operating system, it is still on heavy development
# Usage
first of all you need install ```mtools``` since grub need them to make an iso, ```grub``` to boot the operating system, ```qemu``` to make a VM (Virtual Machine) to run the operating system.
if you are on ArchLinux you can install the dependency
```pacman -S qemu mtools grub nasm``` 
get into the kernel directory, then run ```make``` and then you can either run qemu manually or use the script that i made with ```./qemu.sh``` both works just fine.
# Wiki
you can vist the wiki at https://github.com/09bravo/panos/wiki
# Sources Used
wiki.osdev.org 
