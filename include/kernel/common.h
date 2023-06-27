#ifndef _CB_COMMON_H_
#define _CB_COMMON_H_

#include <stdint.h>

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);
extern void io_wait();
void insl(uint16_t port, unsigned int addr, uint32_t count);

#endif