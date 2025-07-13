#include "drivers/ps2.h"
#include "drivers/timers.h"
void kernel_main() {
  while(1) {
  PIT();
  ps2();
  }
  while (1);
}
