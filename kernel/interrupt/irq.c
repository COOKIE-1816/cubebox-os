#include "kernel/interrupt/irq.h"
#include "kernel/common.h"
#include "drivers/pic.h"
#include <stdint.h>

void irq_setMask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;

        IRQline -= 8;
    }

    value = inb(port) | (1 << IRQline);
    outb(port, value);
}
 
void irq_clearMask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;

        IRQline -= 8;
    }

    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}