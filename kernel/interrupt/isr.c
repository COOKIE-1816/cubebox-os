#include "kernel/interrupt/isr.h"

void exception_handler() {
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}