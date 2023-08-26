#include "kernel/panic.h"
#include "kernel/tty.h"

void panic(string __error) {
     // disable interrupts
    __asm__ volatile ("cli");
    
    Terminal::Cursor::disable();
    
    Terminal::wstring("\n\n\n");
    Terminal::wstring("======= [ KERNEL PANIC ] =======");
}
