#include "drivers/timer.h"
#include "kernel/interrupt/idt.h"
#include <stdint.h>

uint32_t _jiffies = 0;
uint16_t _hz = 0;

void _handler() {
    _jiffies++;
}

void _setFrequency(uint16_t __frequency) {
    _hz = __frequency;
    uint16_t div = CLOCK_FREQUENCY / __frequency;

    outb(TIMER_COMMAND, TIMER_ICW);
    outb(TIMER_DATA,  div & 0xFF);
    outb(TIMER_DATA, (div >> 8) & 0xFF);
}

inline void sleep(int __ms) {
    uint32_t end = _jiffies + __ms * _hz;
    while(_jiffies < end);
}

inline void timer_init() {
    _setFrequency(1000);
    setVect(32, _handler);
}