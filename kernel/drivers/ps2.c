#include "../libs/stdio.h"
#include "ps2.h"
#include "../locales/en_US.h"
#define KEYBOARD_PORT 0x60
#define KEYBOARD_PORT_OFF 0x64
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
	uint8_t uppercase = capslock ^ shift;
	if(uppercase) {
	return ascii_capital_en_US[scancode];
	} else {
	return ascii_en_US[scancode];
	}
}
int ps2_keyboard_scan() {
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
char ps2_keyboard_input() {
	if(inb(KEYBOARD_PORT_OFF) & 0x01) {
	uint8_t scancode = inb(KEYBOARD_PORT);
	return translator(scancode);
	}
	return '\0';
}
