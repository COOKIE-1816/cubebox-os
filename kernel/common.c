#include "kernel/common.h"
#include <stdint.h>

inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" :: "a" (value), "dN" (port));
}

inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile("inb %[port], %[value]" : [value] "=a" (value) : [port] "Nd" (port));
    return value;
}