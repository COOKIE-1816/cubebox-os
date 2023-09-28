#ifndef IRQDEF_H
#define IRQDEF_H

#define IRQ_PIT 0
#define IRQ_KEYBOARD 1
#define IRQ_CASCADE 2
#define IRQ_PIT2 2
#define IRQ_COM2 3
#define IRQ_COM1 4
#define IRQ_LPT2 5
#define IRQ_FLOPPY 6
#define IRQ_LPT1 7
#define IRQ_CMOS_RTC 8
#define IRQ_MOUSE 12
#define IRQ_FPU 13
#define IRQ_COPROCESSOR 13
#define IRQ_ATA_PRIMARY 14
#define IRQ_ATA_SECONDARY 15

#define IRQ_FREE1 9
#define IRQ_FREE2 10
#define IRQ_FREE3 11

#define IRQ_SCSI1 9
#define IRQ_SCSI2 10
#define IRQ_SCSI3 11

#define IRQ_NIC1 9
#define IRQ_NIC2 10
#define IRQ_NIC3 11

#define IRQ_PORT_PIC1_CTRL 20h
#define IRQ_PORT_PIC1_MASK 20h
#define IRQ_PORT_PIC2_CTRL a0h
#define IRQ_PORT_PIC2_MASK a1h

#define IRQ_PORT_KBD_DATA 60h
#define IRQ_PORT_KBD_COMM 64h

#endif