#include "kernel/irq/isr.h"
#include "kernel/irq/idt.h"

void idt_setDescriptor(u8 vector, void* isr, u8 flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (u32) isr & 	0xFFFF;
	descriptor->isr_high       = (u32) isr >> 	0x000F;
    descriptor->kernel_cs      = 				0x0008;
	descriptor->reserved       = 				0x0000;
    descriptor->attributes     = 				flags;
}

static u8 vectors[32];

void idt_init() {
    idtr.base =	(uintptr_t)	&idt[0];
    idtr.limit =(u16)		sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (u8 vector = 0; vector < 32; vector++) {
        idt_setDescriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = 1;
    }
 
    __asm__ volatile (
		"lidt %0" : : 
		"m"
		(idtr)
	);
	
    idt_enable();
}

void idt_enable() {
	__asm__ volatile ("sti");
}

void idt_disable() {
	__asm__ volatile ("cli");
}