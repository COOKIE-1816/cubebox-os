#include "kernel/interrupt/irq.h"
#include "kernel/interrupt/idt.h"
#include "kernel/tty.h"
#include "kernel/common.h"
#include "kernel/system.h"
#include "drivers/pic.h"
#include <stdint.h>

using namespace Kernel::IDT;
using namespace Kernel::System;
//using namespace Kernel::IRQ;

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

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


void Kernel::IRQ::installHandler(int __irq, Kernel::IRQ::irqHandler_t __handler) {
    irq_routines[__irq] = __handler;
    tty_writeString("IRQ: Handler installed.\n");
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

    /*idt_setGate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_setGate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_setGate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_setGate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_setGate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_setGate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_setGate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_setGate(39, (unsigned)irq7, 0x08, 0x8E);

    idt_setGate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_setGate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_setGate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_setGate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_setGate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_setGate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_setGate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_setGate(47, (unsigned)irq15, 0x08, 0x8E);*/
}

extern "C" void Kernel::IRQ::irq_handler(regs *r) {

    unsigned int vector = r->int_no - 32;
    void (*handler)(struct regs *r);

    if (r->int_no > 47 || r->int_no < 32) {
		handler = NULL;
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

