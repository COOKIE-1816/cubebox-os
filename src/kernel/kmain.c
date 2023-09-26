#include "kernel/kernel.h"
#include "kernel/terminal.h"
#include "kernel/gdt.h"

// static gdt_descriptor_template_t* _g[4];

void printVersion() {
    terminal_wstring("Kernel version: \t");
    terminal_wstring(kernel_version);

    if(kernel_devStage != (const char*) "stable") 
		terminal_wstring(kernel_devStage);
	

    terminal_wstring("\n");
}

// extern "C" 
void kmain(void) {
	
	
    terminal_init();

    terminal_setColor(0x02); // Green text
    terminal_wstring("CubeBox OS!\n\n");

    terminal_resetColor();
    printVersion();

    gdt_createDescriptor(0x00, 0x000FFFFF, 0x00);
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL3));
}
