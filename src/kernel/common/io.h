#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include "kernel/kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

void outb(u16 __port, u8 __value);
u8 inb(u16 __port);

void io_wait();
void insl(u16 __port, unsigned int __address, u32 __count);

void outb(u16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" :: "a" (value), "dN" (port));
}

#ifdef __cplusplus
}
#endif

#endif