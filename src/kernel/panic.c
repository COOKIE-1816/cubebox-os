#include "kernel/panic.h"
#include "kernel/terminal.h"

void __halt() {
    terminal_wstring("System halted.");
    
    __asm__ volatile ("cli");
    while(1) {
        // do nothing.
    }
}

void panic(String __error) {
     // disable interrupts
    __asm__ volatile ("cli");
    
    terminal_cursor_disable();
    
    terminal_wstring("\n\n\n");
    terminal_wstring("======= [ KERNEL PANIC ] =======\n");
    
    terminal_wstring("- kernel panic: ");
    terminal_wstring(__error);
    terminal_wstring("\n");
    
    terminal_wstring("End of kernel panic. ");
    __halt();
}

void asmpanic() {
	panic("KERNEL_PANIC_UNK");
}

