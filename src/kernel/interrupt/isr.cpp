#include "kernel/interrupt/isr.h"

void Kernel::ISR::exception_handler() {
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}