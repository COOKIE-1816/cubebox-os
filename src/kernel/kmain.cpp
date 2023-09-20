#include "kernel/kernel.h"
#include "kernel/terminal.h"
#include "kernel/gdt.h"

// static gdt_descriptor_template_t* _g[4];

void printVersion() {
    Terminal::wstring("Kernel version: \t");
    Terminal::wstring(kernel_version);

    #if KDEVSTAGE_STRING != "stable"
        Terminal::wstring(KDEVSTAGE_STRING);
    #endif

    Terminal::wstring("\n");
}

extern "C" 
void kmain(void) {
    Terminal::init();

    Terminal::setColor(0x02); // Green text
    Terminal::wstring("CubeBox OS!\n\n");

    Terminal::resetColor();
    printVersion();

    Gdt::createDescriptor(0x00, 0x000FFFFF, 0x00);
    Gdt::createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL0));
    Gdt::createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL0));
    Gdt::createDescriptor(0x00, 0x000FFFFF, (GDT_CODE_PL3));
    Gdt::createDescriptor(0x00, 0x000FFFFF, (GDT_DATA_PL3));
}