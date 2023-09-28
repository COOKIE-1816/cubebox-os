#ifndef ISR_H
#define ISR_H

__attribute__((noreturn))
void exception_handler(void);

extern void* isr_stub_table[];

#endif