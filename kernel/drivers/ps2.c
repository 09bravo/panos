#include "../libs/stdio.h"
#include "ps2.h"
#include "../locales/en_US.h"
#define KEYBOARD_PORT 0x60
#define KEYBOARD_PORT_OFF 0x64
// The translator take a scancode a scan code and turns it into a readable characters
char translator(uint8_t scancode) {
	static uint8_t capslock = 0;
	static uint8_t shift = 0;
	if(scancode == 0x3A) {
	capslock = !capslock;	
	return '\0';
	}
	if(scancode == 0x2A || scancode == 0x36) {
	shift = 1;	
	return '\0';
	}
	if(scancode == 0xAA || scancode == 0xB6) {
	shift = 0;
	return '\0';
	}
	if(scancode & 0x80) {
	return '\0';
	}
	if(scancode >= sizeof(ascii_en_US)) {
	return '\0';
	}
	if(capslock) {
	return ascii_capital_en_US_no_special_characters[scancode];
	} else if(shift) {
	return ascii_capital_en_US[scancode];
	} else {
	return ascii_en_US[scancode];
	}
}
// we start by scanning for scancodes (which we will use the translator function to turn it into actually characters)
int ps2_keyboard() {
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF0);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0x00);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	if(inb(KEYBOARD_PORT) != 0xFA) {
	return 1;
	}	
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF4);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	if(inb(KEYBOARD_PORT) != 0xFA) return 1;

	return 0;
}
// The input function calls back the ps2_driver function to get the scancode, then get turns the scancode into a readable characters using the translator function, and then the characters are printed with kputs, and it is all looped using a infinity while loop
void ps2_keyboard_input() {
	while(1) {
	if(inb(KEYBOARD_PORT_OFF) & 0x01) {
	uint8_t scancode = inb(KEYBOARD_PORT);
	char c =translator(scancode);
	if(c != '\0') {
	char string[2] = {c, '\0'};
	kprintf(string);
	}
	}
	}
}
