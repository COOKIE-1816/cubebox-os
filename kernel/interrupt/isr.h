#ifndef _CB_INTERRUPT_ISR_H_
#define _CB_INTERRUPT_ISR_H_

void exception_handler(void);

extern void* isr_stub_table[];

#endif