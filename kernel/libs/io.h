#ifndef IO_H
#define IO_H
typedef signed char	int8_t;
typedef unsigned char	uint8_t;
typedef signed short	int16_t;
typedef unsigned short	uint16_t;
typedef signed int	int32_t;
typedef unsigned int	uint32_t;
/* The Os/kernel is currently 32bit and not 64bit, i am planing to change this ofc, but for now this is commented */
//typedef signed long long	int64_t;
//typedef unsigned long long	uint64_t;
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}
static inline void io_wait(void)
{
    outb(0x80, 0);
}
#endif
