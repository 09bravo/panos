// More timers will be added in the "near" (no promises) future
#include "../libs/stdio.h"
#include "timers.h"
void PIT() {
	uint16_t ticks = 1193182 / 1000;
	outb(0x43, 0x36);
	outb(0x40, ticks & 0xFF);
	outb(0x40, (ticks & 0xFF00) >> 8);
}
