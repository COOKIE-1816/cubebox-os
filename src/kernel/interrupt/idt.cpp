#include "kernel/interrupt/idt.h"
#include "kernel/interrupt/isr.h"
//#include <cboolean.h>

using namespace Kernel;
//using namespace Kernel::IDT;

#define IDT_MAX_DESCRIPTORS 256

static void* isr_stub_table[IDT_MAX_DESCRIPTORS];

__attribute__((aligned(0x10))) 
static IDT::idt_entry_t _IDT[IDT_MAX_DESCRIPTORS];
static IDT::idtr_t IDTR;

void Kernel::IDT::setDescriptor(uint8_t __vector, void* __isr, uint8_t __flags) {
    IDT::idt_entry_t *descriptor = &_IDT[__vector];

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


static bool vectors[IDT_MAX_DESCRIPTORS];

void Kernel::IDT::idt_init() {
    IDTR.base = (uintptr_t) &_IDT[0];
    IDTR.limit = (uint16_t) sizeof(IDT::idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    uint8_t vect;

    for (vect = 0; vect < 32; vect++) {
        IDT::setDescriptor(vect, isr_stub_table[vect], 0x8E);
        vectors[vect] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(vect));
    __asm__ volatile ("sti");
}