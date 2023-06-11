#ifndef _CB_ISR_H_
#define _CB_ISR_H_

extern void* isr_stubTable[];

__attribute__((noreturn))
extern void exceptionHandler(void);

#endif
