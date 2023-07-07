#ifndef _CB_INTERRUPT_ISR_H_
#define _CB_INTERRUPT_ISR_H_

namespace Kernel {
    namespace ISR {
        void exception_handler(void);
    };
};

//static void* isr_stub_table[256];

#endif