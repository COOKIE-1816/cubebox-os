#include "kernel/irq/isr.h"
#include "kernel/panic.h"

void exception_handler() {
    //__asm__ volatile ("cli; hlt");
	panic("ISR_IO_EXCEPTION");
}