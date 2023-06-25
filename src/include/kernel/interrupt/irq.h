#ifndef _CB_INTERRUPT_IRQ_H_
#define _CB_INTERRUPT_IRQ_H_

#include "kernel/common.h"

void irq_setMask(unsigned char IRQline);
void irq_clearMask(unsigned char IRQline);

void irq_installHandler(int __irq, void (*__handler)(struct regs *__reg));
void irq_uninstallHandler(int __irq);
void irq_remap();
void irq_init();
void irq_handler(struct regs *r);

#endif