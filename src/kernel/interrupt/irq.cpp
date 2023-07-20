#include "drivers/keyboard.h"
#include "kernel/interrupt/irq.h"
#include "kernel/interrupt/idt.h"
#include "kernel/tty.h"
#include "kernel/common.h"
#include "kernel/system.h"
#include "drivers/pic.h"
#include <stdint.h>

#include "kernel/defs/macros.h"
#include "kernel/defs/vectors.h"

using namespace Kernel::IDT;
using namespace Kernel::IRQ;
using namespace Kernel::System;
using namespace Kernel::TTY;
//using namespace Kernel::IRQ;

extern void irq0() {}
extern void irq1() {}
extern void irq2() {}
extern void irq3() {}
extern void irq4() {}
extern void irq5() {}
extern void irq6() {}
extern void irq7() {}
extern void irq8() {}
extern void irq9() {}
extern void irq10() {}
extern void irq11() {}
extern void irq12() {}
extern void irq13() {}
extern void irq14() {}
extern void irq15() {}

void Kernel::IRQ::setMask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;

        IRQline -= 8;
    }

    value = inb(port) | (1 << IRQline);
    outb(port, value);
}
 
void Kernel::IRQ::clearMask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;

        IRQline -= 8;
    }

    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

static Kernel::IRQ::irqHandler_t irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


void Kernel::IRQ::installHandler(int __irq, irqHandler_t __handler) {
    irq_routines[__irq] = __handler;
    //writeString("IRQ: Handler installed.\n");
}

void Kernel::IRQ::uninstallHandler(int __irq) {
    irq_routines[__irq] = 0;
}

void Kernel::IRQ::remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void Kernel::IRQ::irq_init() {
    remap();

    setDescriptor(32, (unsigned) irq0, 0x08);
    setDescriptor(33, (unsigned) irq1, 0x08);
    setDescriptor(34, (unsigned) irq2, 0x08);
    setDescriptor(35, (unsigned) irq3, 0x08);
    setDescriptor(36, (unsigned) irq4, 0x08);
    setDescriptor(37, (unsigned) irq5, 0x08);
    setDescriptor(38, (unsigned) irq6, 0x08);
    setDescriptor(39, (unsigned) irq7, 0x08);

    setDescriptor(40, (unsigned) irq8, 0x08);
    setDescriptor(41, (unsigned) irq9, 0x08);
    setDescriptor(42, (unsigned) irq10, 0x08);
    setDescriptor(43, (unsigned) irq11, 0x08);
    setDescriptor(44, (unsigned) irq12, 0x08);
    setDescriptor(45, (unsigned) irq13, 0x08);
    setDescriptor(46, (unsigned) irq14, 0x08);
    setDescriptor(47, (unsigned) irq15, 0x08);
}

extern "C" void irq_handler(regs *r, uint32_t __irq, uint32_t __e, uint32_t __eip) {
    UNUSED(__e); // Complete original feature later.
    UNUSED(__eip); // Complete original feature later.

    if(__irq == INTR_KBD) {
        kbd_irqHandler();
        return;
    }

    //writeString("Interrupt handled.");

    unsigned int vector = r->int_no - 32;
    void (*handler)(struct regs *r);

    if (r->int_no > 47 || r->int_no < 32) {
		handler = /*NULL*/ 0;
	} else {
		handler = irq_routines[vector];
	}

    if (handler)
        handler(r);

    if (r->int_no >= 40)
        outb(0xA0, 0x20);

    // END OF INTERRUPT
    outb(0x20, 0x20);
}

