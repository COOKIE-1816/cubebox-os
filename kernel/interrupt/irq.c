//typedef void (*irq_handler_t) (struct regs *)

#include "kernel/interrupt/irq.h"
#include "kernel/common.h"
#include "stddef.h"

static void _irq0();
static void _irq1();
static void _irq2();
static void _irq3();
static void _irq4();
static void _irq5();
static void _irq6();
static void _irq7();
static void _irq8();
static void _irq9();
static void _irq10();
static void _irq11();
static void _irq12();
static void _irq13();
static void _irq14();
static void _irq15();

static irq_handler_t irq_routines[16] = { 
    NULL 
};

void irq_installHandler(int __irq, irq_handler_t __handler) {
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

void irq_gates() {
	/*idt_setGate(32, (unsigned) _irq0,    0x08,   0x8E);
	idt_setGate(33, (unsigned) _irq1,    0x08,   0x8E);
	idt_setGate(34, (unsigned) _irq2,    0x08,   0x8E);
	idt_setGate(35, (unsigned) _irq3,    0x08,   0x8E);
	idt_setGate(36, (unsigned) _irq4,    0x08,   0x8E);
	idt_setGate(37, (unsigned) _irq5,    0x08,   0x8E);
	idt_setGate(38, (unsigned) _irq6,    0x08,   0x8E);
	idt_setGate(39, (unsigned) _irq7,    0x08,   0x8E);
	idt_setGate(40, (unsigned) _irq8,    0x08,   0x8E);
	idt_setGate(41, (unsigned) _irq9,    0x08,   0x8E);
	idt_setGate(42, (unsigned) _irq10,   0x08,   0x8E);
	idt_setGate(43, (unsigned) _irq11,   0x08,   0x8E);
	idt_setGate(44, (unsigned) _irq12,   0x08,   0x8E);
	idt_setGate(45, (unsigned) _irq13,   0x08,   0x8E);
	idt_setGate(46, (unsigned) _irq14,   0x08,   0x8E);
	idt_setGate(47, (unsigned) _irq15,   0x08,   0x8E);*/
}

void irq_install() {
	irq_remap();
	irq_gates();
	IRQ_RES;
}

void irq_ack(int irq_no) {
	if (irq_no >= 12)
		outb(0xA0, 0x20);

	outb(0x20, 0x20);
}

void irq_handler(struct regs *r) {
	IRQ_OFF;

	void (*handler)(struct regs *r);

	if (r->int_no > 47 || r->int_no < 32) {
		handler = NULL;
	} else {
		handler = irq_routines[r->int_no - 32];
	}

	if (handler) {
		handler(r);
	} else {
		irq_ack(r->int_no - 32);
	}

	IRQ_RES;
}