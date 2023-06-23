#include "kernel/interrupt/idt.h"
#include "kernel/interrupt/isr.h"
#include <cboolean.h>

void idt_setDescriptor(uint8_t __vector, void* __isr, uint8_t __flags) {
    idt_entry_t* descriptor = &IDT[__vector];

    #ifndef __E_ARCH_X64
        descriptor->isr_low        = (uint32_t) __isr & 0xFFFF;
        descriptor->kernel_cs      = 0x08;
        descriptor->attributes     = __flags;
        descriptor->isr_high       = (uint32_t) __isr >> 16;
        descriptor->reserved       = 0;
    #else
        descriptor->isr_low        = (uint64_t __)isr & 0xFFFF;
        descriptor->kernel_cs      = GDT_OFFSET_KERNEL_CODE;
        descriptor->ist            = 0;
        descriptor->attributes     = __flags;
        descriptor->isr_mid        = ((uint64_t) __isr >> 16) & 0xFFFF;
        descriptor->isr_high       = ((uint64_t) __isr >> 32) & 0xFFFFFFFF;
        descriptor->reserved       = 0;
    #endif  
}

#define IDT_MAX_DESCRIPTORS 256

static bool vectors[IDT_MAX_DESCRIPTORS];

void idt_init() {
    IDTR.base = (uintptr_t) &IDT[0];
    IDTR.limit = (uint16_t) sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_setDescriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(IDTR));
    __asm__ volatile ("sti");
}