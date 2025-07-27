#include "pinit.h"
#include "../drivers/ps2.h"
#include "../drivers/timers.h"
#include "../libs/stdio.h"
// See https://wiki.osdev.org/Non_Maskable_Interrupt
void NMI_enable() {
    outb(0x70, inb(0x70) & 0x7F);
    inb(0x71);
}

void NMI_disable() {
    outb(0x70, inb(0x70) | 0x80);
    inb(0x71);
}
int pinit() {
	// Disalbe the cursor
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
	// Disabling NMI (Needed to enter proteaced mode (32Bit) then we need to enter long mode (64Bit))
	NMI_disable();
	PIT();
	kprintf("\\G[Starting PIT]\\W\n");
	if(ps2_keyboard() == 0) {
	kprintf("\\G[Starting PS/2 keyborad driver]\\W\n");
	ps2_keyboard_input();
	} else {
	kprintf("\x1bR[Failed to start PS/2 keyborad driver ( if you are sure this isnt a user error please make an issue on github.)]\x1bW");
	return 1;
	}
	return 0;
}
