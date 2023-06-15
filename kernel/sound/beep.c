#include "kernel/sound/beep.h"
#include "drivers/buzzer.h"
#include "drivers/timer.h"

inline void beep() {
    buzzer_makeSound(1000);
    //rtc_sleep(1);
    sleep(750);

    buzzer_stop();
}

