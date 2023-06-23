#include "drivers/pic.h"
#include "kernel/common.h"
#include "kernel/kdrivers.h"

#include <stdint.h>

/*
#define PIC1		    0x20
#define PIC2		    0xA0
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	    (PIC1 + 1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	    (PIC2 + 1)
*/

#define PIC_EOI		    0x20

void pic_sendEOI(unsigned char __irq) {
	if(__irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI);
 
	outb(PIC1_COMMAND, PIC_EOI);
}

#define ICW1_ICW4	    0x01		
#define ICW1_SINGLE	    0x02
#define ICW1_INTERVAL4	0x04	
#define ICW1_LEVEL  	0x08		
#define ICW1_INIT	    0x10		
 
#define ICW4_8086	    0x01		
#define ICW4_AUTO	    0x02		
#define ICW4_BUF_SLAVE	0x08	
#define ICW4_BUF_MASTER	0x0C
#define ICW4_SFNM	    0x10		

void pic_remap(int __offset1, int __offset2) {
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);
 


	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC1_DATA, __offset1);
	io_wait();

	outb(PIC2_DATA, __offset2);
	io_wait();

	outb(PIC1_DATA, 4);
	io_wait();

	outb(PIC2_DATA, 2);
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();

	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 


	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void pic_disable() {
    asm ("mov al, 0xff");
    asm ("out 0xA1, al");
    asm ("out 0x21, al");
}


#define PIC1_CMD                    0x20
#define PIC1_DATA                   0x21
#define PIC2_CMD                    0xA0
#define PIC2_DATA                   0xA1
#define PIC_READ_IRR                0x0a
#define PIC_READ_ISR                0x0b
 
/* Helper func */
static uint16_t _pic_getIrqReg(int __ocw3) {
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, __ocw3);
    outb(PIC2_CMD, __ocw3);

    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
uint16_t pic_getIrr(void) {
    return _pic_getIrqReg(PIC_READ_IRR);
}

uint16_t pic_getIsr(void) {
    return _pic_getIrqReg(PIC_READ_ISR);
}