#include "kernel/interrupt/irq.h"
#include "kernel/interrupt/idt.h"
#include "kernel/common.h"
#include "kernel/system.h"
#include "drivers/pic.h"
#include <stdint.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_setMask(unsigned char IRQline) {
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
 
void irq_clearMask(unsigned char IRQline) {
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

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


void irq_installHandler(int __irq, void (*__handler)/*(struct regs *__reg)*/) {
    irq_routines[__irq] = __handler;
}

void irq_uninstallHandler(int __irq) {
    irq_routines[__irq] = 0;
}

void irq_remap() {
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

void irq_init() {
    irq_remap();

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

void irq_handler(regs *r) {
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);

    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }

    outb(0x20, 0x20);
}

