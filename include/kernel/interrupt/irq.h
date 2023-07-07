#ifndef _CB_INTERRUPT_IRQ_H_
#define _CB_INTERRUPT_IRQ_H_

#include "kernel/common.h"
#include "kernel/system.h"

extern unsigned int __irq_sem;

#define IRQ_OFF { asm volatile ("cli"); }
#define IRQ_RES { asm volatile ("sti"); }
#define IRQS_ON_AND_PAUSE { asm volatile ("sti\nhlt\ncli"); }

//using namespace Kernel::System;

namespace Kernel {
    namespace IRQ {
        typedef void (*irqHandler_t) (struct Kernel::System::regs *r);
        void setMask(unsigned char IRQline);
        void clearMask(unsigned char IRQline);

        void installHandler(int __irq, irqHandler_t __handler);
        void uninstallHandler(int __irq);

        void remap();
        void irq_init();

        extern "C" void irq_handler(Kernel::System::regs *r);
    };
};


#endif