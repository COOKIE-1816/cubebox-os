#include "drivers/pic.h"
#include "kernel/common.h"
#include "kernel/kdrivers.h"

void pic_init() {
    kdriver pic;
    pic.name = "Programmable Interval Controller (PIC)";

    kdriver_statusMsg_create(pic);

    outb(PIC1_COMMAND, ICW1);
    outb(PIC2_COMMAND, ICW1);

    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    outb(PIC1_DATA, 0x4);
    outb(PIC2_DATA, 0x2);

    outb(PIC1_DATA, 1);
    outb(PIC2_DATA, 1);

    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);

    kdriver_statusMsg_status(KDRIVERS_OK);
}

void pic_irq_ack(uint8_t __irq) {
    if(__irq >= 0x28)
        outb(PIC2, PIC_EOI);

    outb(PIC1, PIC_EOI);
}
