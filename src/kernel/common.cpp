#include "kernel/common.h"
#include <stdint.h>

 void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" :: "a" (value), "dN" (port));
}

 uint8_t inb(uint16_t port) {
    uint8_t value;
    
    asm volatile(   "inb %[port], %[value]" 
                    : [value] "=a" (value) 
                    : [port] "Nd" (port)
    );

    return value;
}

 void io_wait() {
    asm volatile("jmp 1f\n\t"
                 "1:jmp 2f\n\t"
                 "2:");
}

void insl(uint16_t port, unsigned int addr, uint32_t count){
    asm volatile("cld; rep insl"
                 : "=D" (addr), "=c" (count)
                 : "d" (port), "0" (addr), "1" (count)
                 : "memory");
}
