#include "drivers/pic.h"
#include "kernel/common.h"
#include "kernel/kdrivers.h"

#include <stdint.h>

static uint16_t ocw1 = 0xFFFB;


#define PIC_MASTER_CTRL 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CTRL  0xA0
#define PIC_SLAVE_DATA  0xA1


void pic_init(void) {
    kdriver pic;
    pic.name = "Programmable Interrupt Controller (PIC)";

    kdriver_statusMsg_create(pic);

    outb(PIC_MASTER_CTRL, 0x11);
    outb(PIC_SLAVE_CTRL, 0x11); 
    
    outb(PIC_MASTER_DATA, 0x20);
    outb(PIC_SLAVE_DATA, 0x28); 
    
    outb(PIC_MASTER_DATA, 0x04);
    outb(PIC_SLAVE_DATA, 0x02); 
    
    outb(PIC_MASTER_DATA, 0x01);
    outb(PIC_SLAVE_DATA, 0x01); 

    outb(PIC_MASTER_DATA, 0xFF);
    outb(PIC_SLAVE_DATA, 0xFF);

    __asm__ __volatile__("nop");

    kdriver_statusMsg_status(KDRIVERS_OK);
}

void irq_enable(uint8_t irq) {
	ocw1 &= (uint16_t)~((1 << irq));

	if (irq < 8)
		outb(PIC_MASTER_DATA, (uint8_t)(ocw1 & 0xFF));
	else
		outb(PIC_SLAVE_DATA, (uint8_t)(ocw1 >> 8));
}

void pic_ack(uint8_t irq) {
    if ( irq > 7)
        outb(PIC_SLAVE_CTRL, 0x20);

    outb(PIC_MASTER_CTRL, 0x20);
}