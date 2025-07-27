# Overview
Panos is a lightweight operating system, it is still under heavy development
# Dependencies
First of all you need to install ```i686-elf-as``` which if you are in Arch Linux you sadly only have two options, A: (not recommend) AUR, use the AUR at your own risk since it is not moderated by the Arch Linux moderators, B: (recommend) Homebrew, Homebrew is an alternative package manager that you can use in most if not all of GNU/Linux distributions (and MacOS but I will not get into this now, maybe on the future), now if you are wondering about dependency hell, don't be, we will only use homebrew to install i686-elf-* so dependency hell won't be much of a problem since we only will ever install 3 packages from homebrew, to install homebrew you can follow the interactions in [brew](https://github.com/Homebrew/brew), some distributions might have i686-elf-* in their official repositories, so check before installing Homebrew, and then run ```brew install i686-elf-as i686-elf-gcc i386-elf-gdb```, it is worth noting that Homebrew does not include i686-elf-gdb but i386-elf-gdb still works fine (As far as I know), you need ```mtools``` since xorriso needs them to make an iso, ```xorriso``` the tool to make the iso itself,```grub``` to boot the operating system, ```qemu``` to make a VM (Virtual Machine) to run the operating system.
if you are on Arch Linux you can install all of the dependency (expect for the ones that need homebrew) with ```pacman -S qemu mtools grub xorriso```
# Usage 
get into the kernel directory, then run ```make``` and then you can either run qemu manually or use the script that I made with ```./qemu.sh``` both works just fine.
# Wiki
You can vist the wiki at https://github.com/09bravo/panos/wiki
# Sources Used
wiki.osdev.org
