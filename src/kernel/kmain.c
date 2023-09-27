#include "kernel/kernel.h"
#include "kernel/terminal.h"
#include "kernel/panic.h"
#include "kernel/gdt.h"

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

    terminal_cursor_move(terminal_pos_x, terminal_pos_y);

    gdt_createDescriptor(0x00, 0x000FFFFF, 0x00);
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL3));

    #ifdef __ALLOW_KERNEL_PANIC_TEST
        panic("KERNEL_PANIC_TEST");
    #endif
}
