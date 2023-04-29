#pragma once

typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

idt_gate_t idt[256];
void idt_setGate(int n, uint32_t handler);
idt_register_t idt_reg;
void idt_load()