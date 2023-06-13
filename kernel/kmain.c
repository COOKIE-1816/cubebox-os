#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/gdt/gdt.h"
#include "kernel/gdt/gdtdef.h"
#include "drivers/keyboard.h"
#include "kernel/common.h"
#include "stringt.h"
//#include "stdlib.h"
//#include "kernel/bootinfo.h"

#define NULL 0x00

/*#ifndef KERNEL_REL_STABLE
    String unstableWarning = "WARNING: UNSTABLE RELEASE, USE AT YOUR OWN RISK!\n";
#else
    String unstableWarning = "";
#endif*/

void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        tty_writeString("-");
}

void kernel_initializeKernelParticipals() {
    tty_initialize();
}

/*unsigned char* stringMem(size_t __size) {
    unsigned char* memoryPtr = (unsigned char*) 0;
    unsigned char* currentPtr = memoryPtr;

    while (__size > 0) {
        *currentPtr = 0;
        currentPtr++;
        __size--;
    }

    return memoryPtr;
}*/

void kernel_main(/*multiboot_info* __boot_info*/ void) {
    kernel_initializeKernelParticipals();

    tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n");
    tty_writeString("Copyright (C) Vaclav Hajsman 2023\n");
    drawLine();

    /*unsigned short total;
    unsigned char lowmem, highmem;
    String buffer;

    outb(0x70, 0x30);
    lowmem = inb(0x71);
    outb(0x70, 0x31);
    highmem = inb(0x71);
 
    total = lowmem | highmem << 8;*/
    
    //*((short*)buffer)  = total;   


    gdt_createDescriptor(0, 0x00000000, 0x000000      );
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    
    keyboard_leds_set(true, true, false);
    keyboard_init(NULL);
}