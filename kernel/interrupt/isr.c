#include "kernel/interrupt/isr.h"

//__attribute__ ((noreturn))
void exceptionHandler()  {
    __asm__ volatile ("cli; hlt");
};
