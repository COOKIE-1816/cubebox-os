#pragma once
#include <stdint.h>

typedef void (*isr_t)(isr_registers_t*);
isr_t isr_interruptHandlers[256];

char* isr_exceptionMessages[] = {
    "Division by zero",
    "Debug",
    "Reserved"
};

void isr_handler(isr_registers_t* r);

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} isr_registers_t;

void irq_handler(isr_registers_t* r)