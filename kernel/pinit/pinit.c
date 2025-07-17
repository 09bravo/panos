#include "pinit.h"
#include "../drivers/ps2.h"
#include "../drivers/timers.h"
#include "../libs/stdio.h"
int pinit() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
	PIT();
	kputs("\\G[Starting PIT]\\W\n");
	if(ps2_keyboard_scan() == 0) {
	kputs("\\G[Starting PS/2 keyborad driver]\\W\n");
	while(1) {
	char c = ps2_keyboard_input();
	if(c != '\0') {
	char str[2] = {c, '\0'};
	kputs(str);
	}
	}
	} else {
	kputs("\x1bR[Failed to start PS/2 keyborad driver ( if you are sure this isnt a user error please make an issue on github.)]\x1bW");
	}
	return 0;
}
