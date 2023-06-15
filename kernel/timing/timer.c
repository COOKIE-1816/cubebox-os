#include "kernel/timing/timer.h"
#include "kernel/interrupt/idt.h"

volatile int _sleepFlag;

void _timerHandler() {
    _sleepFlag = 1;
}

inline void sleep(int __ms) {
    _sleepFlag = 0;
    int ticks = __ms / 10;

    setVect(0x20, _timerHandler);
    asm("sti");

    while(_sleepFlag < ticks);
    //asm("cli");
}