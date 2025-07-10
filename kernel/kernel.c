#include "drivers/ps2.h"
#include "libs/stdio.h"
void kernel_main() {
  ps2();
  while (1);
}
