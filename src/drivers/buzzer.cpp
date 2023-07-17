#include "drivers/buzzer.h"
#include "kernel/common.h"

// ! WARNING:   For QEMU users - be sure to use QEMU with `-soundhw pcspk`.
//              This is required to play sounds.

void buzzer_makeSound(uint32_t __frequency) {
    uint32_t div;
    uint8_t temp;

    div = 1193180 / __frequency;

    outb(0x43, 0xB6);
    outb(0x42, (uint8_t) (div));
    outb(0x42, (uint8_t) (div >> 8));

    temp = inb(0x61);

    if(temp != (temp | 3))
        outb(0x61, temp | 3);
}

void buzzer_stop() {
    uint8_t temp = inb(0x61) & 0xFC;
    outb(0x61, temp);
}