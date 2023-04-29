#include "isr.h"
#include "../pic/pic.h"
#include "../idt/idt.h"
#include "../tty/tty.h"

typedef void (*isr_t)(isr_registers_t*);
isr_t isr_interruptHandlers[256];

void isr_handler(isr_registers_t* r) {
    println(isr_exceptionMessages[r->int_no]);
}

void isr_init() {
    idt_setGate(0, (uint32_t)isr0);
    idt_setGate(1, (uint32_t)isr1);
    idt_setGate(31, (uint32_t)isr31);

    pic_remap();

    idt_setGate(32, (uint32_t)irq0);
    idt_setGate(39, (uint32_t)irq7);
    idt_setGate(40, (uint32_t)irq8);
    idt_setGate(47, (uint32_t)irq15);
}

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} isr_registers_t;

void irq_handler(isr_registers_t* r) {
    if (isr_interruptHandlers[r->int_no] != 0) {
        isr_t handler = isr_interruptHandlers[r->int_no];
        handler(r);
    }

    port_byte_out(0x20, 0x20);

    if (r->int_no < 40)
        port_byte_out(0xA0, 0x20);
}