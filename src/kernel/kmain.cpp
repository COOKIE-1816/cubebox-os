#include "kernel/kernel.h"
#include "kernel/terminal.h"
#include "kernel/gdt.h"

// static gdt_descriptor_template_t* _g[4];

void printVersion() {
    Terminal::wstring("Kernel version: \t");
    Terminal::wstring(kernel_version);

    if(kernel_devStage != (const char*) "stable") 
		Terminal::wstring(kernel_devStage);
	

    Terminal::wstring("\n");
}

extern "C" void kmain(void) {
	
	Gdt gdtobj;
    Terminal::init();

    Terminal::setColor(0x02); // Green text
    Terminal::wstring("CubeBox OS!\n\n");

    Terminal::resetColor();
    printVersion();

    gdtobj.createDescriptor(0x00, 0x000FFFFF, 0x00);
    gdtobj.createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL0));
    gdtobj.createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL0));
    gdtobj.createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL3));
    gdtobj.createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL3));
}
