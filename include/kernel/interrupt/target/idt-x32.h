#ifndef _CB_IDT_TARGET_X32_
#define _CB_IDT_TARGET_X32_

#include <stdint.h>

namespace Kernel {
    namespace IDT {
        typedef struct {
            uint16_t    isr_low;
            uint16_t    kernel_cs;
            uint8_t     reserved;
            uint8_t     attributes;
            uint16_t    isr_high;
        } __attribute__((packed)) idt_entry_t;

        typedef struct {
            uint16_t	limit;
            uint32_t	base;
        } __attribute__((packed)) idtr_t;
    };
};

#endif