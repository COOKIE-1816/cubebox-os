#include "drivers/pit.h"
#include "kernel/common.h"
#include "kernel/system.h"
#include "kernel/interrupt/irq.h"
#include "kernel/kdrivers.h"
#include "kernel/tty.h"

#define PIT_CMD 0x43
#define PIT_DIV 0x40

using namespace Kernel::System;
using namespace Kernel::Kdrivers;
using namespace Kernel::IRQ;

kdriver _pit;

int _pit_ticks = 0;

void _pit_handler(struct regs *__r) {
    Kernel::TTY::writeString("PIT TICK\n");
    _pit_ticks++;
}

void PIT::phase(int __frequency) {
    int divisor = 1193180 / __frequency;

    outb(PIT_CMD, 0x36);

    outb(PIT_DIV, divisor & 0xFF);
    outb(PIT_DIV, divisor >> 8);
}

void PIT::pit_init() {
    _pit.name = "Programmable Interval Controller (PIT)";
    statusMsg_create(_pit);

    installHandler(0, _pit_handler);

    statusMsg_status(KDRIVERS_OK);
}

void PIT::wait(int __ticks) {
    unsigned long targetTicks = _pit_ticks + __ticks;

    while(_pit_ticks < targetTicks);
}