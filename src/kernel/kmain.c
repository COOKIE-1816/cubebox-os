#include "kernel/kernel.h"
#include "kernel/terminal.h"
#include "kernel/panic.h"
#include "kernel/gdt.h"
#include "kernel/interrupts.h"

#include "drivers/serial/serial.h"

// static gdt_descriptor_template_t* _g[4];


void printVersion() {
    terminal_wstring("Kernel version: ");
    terminal_wstring(kernel_version);
    terminal_wstring(" ");

    if(kernel_devStage != (const char*) "stable") 
		    terminal_wstring(kernel_devStage);
	
    terminal_wstring("\n");
}

// #define __ALLOW_KERNEL_PANIC_TEST

// extern "C" 
void kmain(void) {
	
	
    terminal_init();

    terminal_setColor(0x02); // Green text
    terminal_wstring("CubeBox OS!\n");

    terminal_resetColor();
    printVersion();
    terminal_wstring("\n");

	terminal_cursor_disable();
	
	gdt_install();
	idt_init();
	
	serial_init();
	
	
    #ifdef __ALLOW_KERNEL_PANIC_TEST
        panic("KERNEL_PANIC_TEST");
    #endif
	
	__asm__ volatile ("cli");
    while(1) {
        // do nothing.
    }
}
