SOURCES := kernel.c pinit/pinit.c $(wildcard libs/*.c) $(wildcard drivers/*.c)
OBJECTS := $(SOURCES:.c=.o)

all: panos.iso
%.o: %.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
boot.o: boot.asm
	i686-elf-as $< -o $@
a20line.o: a20line.asm
	nasm -f elf32 a20line.asm -o $@
panos.bin: linker.ld boot.o a20line.o $(OBJECTS)
	i686-elf-gcc -T linker.ld -o panos.bin -ffreestanding -O2 -nostdlib boot.o a20line.o $(OBJECTS) -lgcc
panos.iso: panos.bin
	cp panos.bin isodir/boot/panos.bin
	grub-mkrescue -o panos.iso isodir
clean:
	rm -Rf *.bin *.o *.bin *.iso isodir/boot/*.bin drivers/*.o libs/*.o
.PHONY: all clean
