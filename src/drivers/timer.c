#include "drivers/timer.h"
#include "kernel/interrupt/idt.h"
#include "kernel/kdrivers.h"
#include <stdint.h>

volatile uint32_t _ticks = 0;

void _timer_handler() {  
    _ticks++;
}

void timer_init() {
    uint16_t divisor = 1193; // 1 kHz frequency

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);

    //setVect(0x20, _timer_handler);
}

uint32_t timer_getTicks() {
    return _ticks;
}