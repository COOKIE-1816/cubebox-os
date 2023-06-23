#ifndef _CB_BUZZER_H_
#define _CB_BUZZER_H_

#include <stdint.h>

extern void buzzer_makeSound(uint32_t __frequency);
extern void buzzer_stop();

#endif