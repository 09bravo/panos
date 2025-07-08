void kernel_main() {
  volatile char *vga = (volatile char*) 0xB8000;
  char massage[] = "Hello World";
  for(int i = 0; massage[i] != '\0'; i++) {
  vga[i * 2] = massage[i];
  vga[i * 2 + 1] = 0x03;
  }
  for(;;);
}
