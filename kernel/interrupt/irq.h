#ifndef _CB_IRQ_H_
#define _CB_IRQ_H_

#include "kernel/kernel.h"

#define IRQ_OFF { asm volatile ("cli"); }
#define IRQ_RES { asm volatile ("sti"); }
#define PAUSE   { asm volatile ("hlt"); }
#define IRQS_ON_AND_PAUSE { asm volatile ("sti\nhlt\ncli"); }

void _irq0();
void _irq1();
void _irq2();
void _irq3();
void _irq4();
void _irq5();
void _irq6();
void _irq7();
void _irq8();
void _irq9();
void _irq10();
void _irq11();
void _irq12();
void _irq13();
void _irq14();
void _irq15();

typedef void (*irq_handler_t) (struct regs *);

void irq_installHandler(int __irq, irq_handler_t __handler);
void irq_uninstallHandler(int __irq);
void irq_remap();
void irq_gates();
void irq_install();
void irq_ack(int irq_no);
void irq_handler(struct regs *r);

#endif