#include "kernel/common/io.h"

void outb(u16 __port, u8 __value) {
    asm volatile ("outb %0, %1" :: "a" (__value), "dN" (__port));
}
