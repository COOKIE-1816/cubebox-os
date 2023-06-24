#ifndef _CB_INTERRUPT_IDT_H_
#define _CB_INTERRUPT_IDT_H_

#include <stdint.h>

#ifndef __E_ARCH_X64
    typedef struct {
        uint16_t    isr_low;
        uint16_t    kernel_cs;
        uint8_t     reserved;
        uint8_t     attributes;
        uint16_t    isr_high;
    } __attribute__((packed)) idt_entry_t;
#else
    typedef struct {
        uint16_t    isr_low;
        uint16_t    kernel_cs;
        uint8_t	    ist;
        uint8_t     attributes;
        uint16_t    isr_mid;
        uint32_t    isr_high;
        uint32_t    reserved;
    } __attribute__((packed)) idt_entry_t;
#endif



#ifndef __E_ARCH_X64
    typedef struct {
        uint16_t	limit;
        uint32_t	base;
    } __attribute__((packed)) idtr_t;
#else
    typedef struct {
        uint16_t	limit;
        uint64_t	base;
    } __attribute__((packed)) idtr_t;
#endif


void idt_setDescriptor(uint8_t __vector, void* __isr, uint8_t __flags);
void idt_init();

#endif