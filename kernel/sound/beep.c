#include "kernel/sound/beep.h"
#include "drivers/buzzer.h"
#include "kernel/timing/rtc.h"

inline void beep() {
    buzzer_makeSound(1000);
    rtc_sleep(1);

    buzzer_stop();
}