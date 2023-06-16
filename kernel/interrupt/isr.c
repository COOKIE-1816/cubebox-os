#include "kernel/interrupt/isr.h"

void exceptionHandler() {
    __asm__ volatile ("cli; hlt");
}
