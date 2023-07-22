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

#ifdef __cplusplus
}
#endif

#endif