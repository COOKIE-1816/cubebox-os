#ifndef _CB_PIC_H_
#define _CB_PIC_H_

#include <stdint.h>

#define PIC_MASTER_CTRL 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CTRL  0xA0
#define PIC_SLAVE_DATA  0xA1

void pic_init(void);
void irq_enable(uint8_t irq);
void pic_ack(uint8_t irq);

#endif