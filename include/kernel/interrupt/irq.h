#ifndef _CB_INTERRUPT_IRQ_H_
#define _CB_INTERRUPT_IRQ_H_

#include "kernel/common.h"
#include "kernel/system.h"

using namespace Kernel::System;

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

        extern void installHandler(int __irq, irqHandler_t __handler);
        void uninstallHandler(int __irq);

        void remap();
        void irq_init();

        //extern "C" void irq_handler(regs *__r);
    };
};

extern "C" void irq_handler(regs *__r, 
                            uint32_t __irq, 
                            uint32_t __e, 
                            uint32_t __eip);

#endif