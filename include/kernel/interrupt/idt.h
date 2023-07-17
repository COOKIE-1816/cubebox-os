#ifndef _CB_INTERRUPT_IDT_H_
#define _CB_INTERRUPT_IDT_H_

#include <stdint.h>

#ifndef __E_ARCH_X64
    #include "kernel/interrupt/target/idt-x32.h"
#else
    #include "kernel/interrupt/target/idt-x64.h"
#endif

namespace Kernel {
    namespace IDT {
        void setDescriptor(uint8_t __vector, unsigned __isr, uint8_t __flags);
        void idt_init();
    };
};


#endif