#ifndef _CB_TIMER_H_
#define _CB_TIMER_H_

#define CLOCK_FREQUENCY 1193180
#define TIMER_COMMAND 0x43
#define TIMER_DATA 0x40
#define TIMER_ICW 0x36

extern void sleep(int __ms);
extern void timer_init();

#endif