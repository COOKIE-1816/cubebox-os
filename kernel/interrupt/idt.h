#ifndef _CB_IDT_H_
#define _CB_IDT_H_

#define IDT_MAX_DESCRIPTORS 512

#include <stdint.h>
#include "kernel/interrupt/isr.h"

uint8_t* vectors;

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

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];
static idtr_t idtr;

void idt_setDescriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);

#endif