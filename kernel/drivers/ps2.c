#include "../libs/stdio.h"
#include "ps2.h"
#include "../locales/en_US.h"
#define KEYBOARD_PORT 0x60
#define KEYBOARD_PORT_OFF 0x64
char translator(uint8_t scancode) {
	static short capital = 0; 
	if(scancode == 0x3A || scancode == 0x2A || scancode == 0x36) {
	capital = !capital;	
	return '\0';
	}
	if(scancode == 0xAA || scancode == 0xB6) {
	capital = 0;
	return '\0';
	}
	if(capital == 0) {
	if(scancode >= sizeof(ascii_en_US)) return '\0';
	return ascii_en_US[scancode];
	} else {
	if(scancode >= sizeof(ascii_capital_en_US)) return '\0';
	return ascii_capital_en_US[scancode];
	}
}
void ps2() {
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF0);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0x00);
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	if(inb(KEYBOARD_PORT) != 0xFA) {
	kputs("PS/2 keyborad driver: Failed to scan. if your are sure this isn't a user error please make an issue on github.");
	return;
	}
	
	while(inb(KEYBOARD_PORT_OFF) & 0x02);
	outb(KEYBOARD_PORT, 0xF4);
	while(!(inb(KEYBOARD_PORT_OFF) & 0x01));
	if(inb(KEYBOARD_PORT) != 0xFA) return;
	while(1) {
	if(inb(KEYBOARD_PORT_OFF) & 0x01) {
	uint8_t scancode = inb(KEYBOARD_PORT);
	char c = translator(scancode);
	if(c != '\0') {
	char str[2] = {c, '\0'};
	kputs(str);
	}
	}
	}
}
