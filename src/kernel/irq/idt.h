#ifndef IDT_H
#define IDT_H

#define IDT_MAX_DESCRIPTORS 256

#include "kernel/kernel.h"

typedef struct {
	u16 isr_low;
	u16 isr_high;
	u16 kernel_cs;
	u8	reserved;
	u8  attributes;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	u16	limit;
	u32	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];

static idtr_t idtr;

void idt_setDescriptor(u8 vector, void* isr, u8 flags);
void idt_init(void);

void idt_enable();
void idt_disable();

void idt_installHandler(u8 __vector, void* __handler_ptr);

#endif