#ifndef STDIO_H
#define STDIO_H
typedef signed char       int8_t;
typedef unsigned char   uint8_t;
typedef signed short    int16_t;
typedef unsigned short  uint16_t;
typedef signed int      int32_t;
typedef unsigned int    uint32_t;
/* The Os/kernel is currently 32bit and not 64bit, i am planing to change this ofc, but for now this is commented */
//typedef signed long long      int64_t;
//typedef unsigned long long    uint64_t;
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);
void kprintf(char *str);
#endif
