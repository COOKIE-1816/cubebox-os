#include "kernel/common/io.h"

u8 inb(u16 __port) {
    u8 value;
    
    asm volatile(   "inb %[__port], %[value]" 
                    : [value] "=a" (value) 
                    : [__port] "Nd" (__port)
    );

    return value;
}