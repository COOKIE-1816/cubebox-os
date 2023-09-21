#include "kernel/panic.h"
#include "kernel/terminal.h"

void __halt() {
    Terminal::wstring("System halted.");
    
    __asm__ volatile ("cli");
    while(1) {
        // do nothing.
    }
}

void panic(String __error) {
     // disable interrupts
    __asm__ volatile ("cli");
    
    Terminal::Cursor::disable();
    
    Terminal::wstring("\n\n\n");
    Terminal::wstring("======= [ KERNEL PANIC ] =======\n");
    
    Terminal::wstring("- kernel panic: ");
    Terminal::wstring(__error);
    Terminal::wstring("\n");
    
    Terminal::wstring("End of kernel panic. ");
    __halt();
}

void asmpanic() {
	panic("KERNEL_PANIC_UNK");
}

