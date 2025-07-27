#include "stdio.h"
typedef signed char	int8_t;
typedef unsigned char	uint8_t;
typedef signed short	int16_t;
typedef unsigned short	uint16_t;
typedef signed int	int32_t;
typedef unsigned int	uint32_t;
/* The OS/kernel is currently 32bit and not 64bit, i am planing to change this ofc, but for now this is commented */
//typedef signed long long	int64_t;
//typedef unsigned long long	uint64_t;
typedef unsigned long	size_t;
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
// tracks text postion
static int pos = 0;
void kprintf(char *str) {
  volatile char *vga = (volatile char*) 0xB8000;
  /* the default color is white on a black background, if you wish to change it you can change it like this "kputs("\\B blue text!\\W white text!")", in the old versions however, it used to be like this "kputs("\x1bBThis is a blue text! again ! \\Wwhite text! again!")", it used to be like this because I used to type \x1b a lot when I was making Krab but I have decide it was unnecessary, if you was to see more vga color codes please see https://github.com/09bravo/panos/wiki/VGA-Color-codes for more information */
  uint8_t color = 0x0F;
  for(int i = 0; str[i] != '\0'; i++) {
  if(str[i] == '\\') {
  i++;
  switch(str[i]) {
	case 'R': color = 0x04; break;
	case 'G': color = 0x0A; break;
	case 'B': color = 0x01; break;
	case 'W': color = 0x07; break;
	case 'D': color = 0x07; break;
	default: break;
  }
  continue;
  }
  if(str[i] == '\b') {
  if(pos > 0) {
	pos--;
	vga[pos * 2] = ' ';
	vga[pos * 2 + 1] = color;
	}
  } else if(str[i] == '\n') {
   pos = ((pos / 80) + 1) * 80;
  }
  else {
  vga[pos * 2] = str[i];
  vga[pos * 2 + 1] = color;
  pos++;
  }
  }
}
