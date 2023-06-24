#ifndef _CB_PIC_H_
#define _CB_PIC_H_

#include <stdint.h>

#define PIC1		    0x20
#define PIC2		    0xA0
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	    (PIC1 + 1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	    (PIC2 + 1)

void pic_sendEOI(unsigned char __irq);
void pic_remap(int __offset1, int __offset2);

//void pic_disable();

uint16_t pic_getIrr();
uint16_t pic_getIsr();

#endif