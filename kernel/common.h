#ifndef _CB_COMMON_H_
#define _CB_COMMON_H_

#include <stdint.h>

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);

#endif