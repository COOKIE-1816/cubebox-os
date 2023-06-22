#ifndef _CB_IRQ_H_
#define _CB_IRQ_H_

#include "kernel/kernel.h"

#define IRQ_OFF { asm volatile ("cli"); }
#define IRQ_RES { asm volatile ("sti"); }
#define PAUSE   { asm volatile ("hlt"); }
#define IRQS_ON_AND_PAUSE { asm volatile ("sti\nhlt\ncli"); }



typedef void (*irq_handler_t) (struct regs *);

void irq_installHandler(int __irq, irq_handler_t __handler);
void irq_uninstallHandler(int __irq);
void irq_remap();
void irq_gates();
void irq_install();
void irq_ack(int irq_no);
void irq_handler(struct regs *r);

#endif