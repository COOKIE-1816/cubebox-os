#include "kernel/common/io.h"

void io_wait() {
    asm volatile(   "jmp 1f\n\t"
                    "1:jmp 2f\n\t"
                    "2:");
}

void insl(u16 __port, unsigned int __address, u32 __count) {
    asm volatile(   "cld; rep insl"
                    : "=D" (__address), "=c" (__count)
                    : "d" (__port), "0" (__address), "1" (__count)
                    : "memory");
}