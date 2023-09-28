#include "kernel/panic.h"
#include "kernel/terminal.h"
#include "drivers/vga/vga.h"

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
    
    terminal_wstring("\n");
    terminal_wstring("======= [ KERNEL PANIC ] ");

    for(int i = 0; i < VGA_WIDTH - 25; i++)
        terminal_wstring("=");

    // No need to make a line break, since it is already
    // made by printing those "equal to" marks.
    
    terminal_setColor(0b10001100);
    terminal_wstring("- kernel panic: ");
    terminal_wstring(__error);
    terminal_wstring("\n");

    terminal_setColor(0x07);
    
    terminal_wstring("End of kernel panic. ");
    __halt();
}

void asmpanic() {
    terminal_wstring("End of kernel initialization routines ( kmain() ).\n");
	panic("KERNEL_PANIC_UNK");
}

