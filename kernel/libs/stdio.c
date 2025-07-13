#include "stdio.h"
typedef signed char	int8_t;
typedef unsigned char	uint8_t;
typedef signed short	int16_t;
typedef unsigned short	uint16_t;
typedef signed int	int32_t;
typedef unsigned int	uint32_t;
/* The Os/kernel is currently 32bit and not 64bit, i am planing to change this ofc, but for now this is commented */
//typedef signed long long	int64_t;
//typedef unsigned long long	uint64_t;
void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}
void io_wait(void)
{
    outb(0x80, 0);
}
static int pos = 0;
void kputs(char *str) {
  volatile char *vga = (volatile char*) 0xB8000;
  for(int i = 0; str[i] != '\0'; i++) {
  if(str[i] == '\b') {
  if(pos > 0) {
	pos--;
	vga[pos * 2] = ' ';
	vga[pos * 2 + 1] = 0x03;
	}
  } else if(str[i] == '\n') {
   pos = (pos / 80 + 1) * 80;
  }
  else {
  vga[pos * 2] = str[i];
  vga[pos * 2 + 1] = 0x03;
  pos++;
  }
  }
}
