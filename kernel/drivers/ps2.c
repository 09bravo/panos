#include "../libs/io.h"
#include "../libs/stdio.h"
#include "ps2.h"
#define KEYBOARD_PORT 0x60
#define KEYBOARD_PORT_OFF 0x64
void ps2() {
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF0);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0x00);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	uint8_t response = inb(KEYBOARD_PORT);
	if(response == 0xFA) {	
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF4);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	response = inb(KEYBOARD_PORT);
	if(response == 0xFA) {
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	uint8_t scancode = inb(KEYBOARD_PORT);
	kprintf("{x}", scancode);
	}
	} else {
	kputs("Failed to detect a PS/2 device, if you are sure this isnt a user error please make an issue on github.");
	}
}
