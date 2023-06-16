#ifndef _CB_IRQ_H_
#define _CB_IRQ_H_

#include "kernel/kernel.h"

#define IRQ_OFF { asm volatile ("cli"); }
#define IRQ_RES { asm volatile ("sti"); }
#define PAUSE   { asm volatile ("hlt"); }
#define IRQS_ON_AND_PAUSE { asm volatile ("sti\nhlt\ncli"); }

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

typedef void (*irq_handler_t) (struct regs *);

void irq_installHandler(int __irq, irq_handler_t __handler);
void irq_uninstallHandler(int __irq);
void irq_remap();
void irq_gates();
void irq_install();
void irq_ack(int irq_no);
void irq_handler(struct regs *r);

#endif