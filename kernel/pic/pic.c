#include "pic.h"

void pic_remap(int offset1, int offset2) {
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
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

void pic_disable(void) {
	asm("mov al, 0xff");
	asm("out 0xa1, al");
	asm("out 0x21, al");
}

static uint16_t __pic_getIrqReg(int ocw3) {
	outb(PIC1_CMD, ocw3);
	outb(PIC2_CMD, ocw3);
	return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}

uint16_t pic_getIrr(void) {
	return __pic_getIrqReg(PIC_READ_IRR);
}

uint16_t pic_getIsr(void) {
	return __pic_getIrqReg(PIC_READ_ISR);
}