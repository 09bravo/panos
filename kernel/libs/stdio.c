#include "stdio.h"
void kputs(char *str) {
  volatile char *vga = (volatile char*) 0xB8000;
  for(int i = 0; str[i] != '\0'; i++) {
  vga[i * 2] = str[i];
  vga[i * 2 + 1] = 0x03;
  }
}
const char *hex(uint8_t val) {
static char buf[3];
const char hex_chars[] = "0123456789ABCDEF";
buf[2] = '\0';
buf[1] = hex_chars[val & 0xF];
buf[0] = hex_chars[(val >> 4) & 0xF];
return buf;
}
void kprintf(const char *str, uint8_t val) {
	int i = 0;
	volatile char *vga = (volatile char*) 0xB8000;
	static int pos = 0;
	while(str[i] != '\0') {
	if(str[i] == '{' && str[i + 1] == 'x' && str[i + 2] == '}') {
	const char *hex_str = hex(val);
	for(int j = 0; hex_str[j] != '\0'; j++) {
	static int pos = 0;
	vga[pos * 2] = hex_str[j];
	vga[pos * 2 + 1] = 0x03;
	pos++;
	}
	i += 3;
	} else {
	vga[pos * 2] = str[i];
	vga[pos * 2 + 1] = 0x03;
	pos++;
	i++;
	}
	}
}
