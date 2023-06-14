#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/gdt/gdt.h"
#include "kernel/gdt/gdtdef.h"
#include "drivers/keyboard.h"
#include "kernel/common.h"
#include "stringt.h"
#include "kernel/timing/rtc.h"
//#include "stdlib.h"
//#include "kernel/bootinfo.h"

//#define NULL 0x00
#include <stddef.h>

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

enum KEYCODE getKey() {
    enum KEYCODE k = KEY_UNKNOWN;

    while(k == KEY_UNKNOWN)
        k = keyboard_getLastKey();
    
    keyboard_discardLastKey();
    return k;
}

void kernel_main(/*multiboot_info* __boot_info*/ void) {
    kernel_initializeKernelParticipals();

    tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n");
    tty_writeString("Copyright (C) Vaclav Hajsman 2023\n");
    drawLine();

    //*((short*)buffer)  = total;   


    /*gdt_createDescriptor(0, 0x00000000, 0x000000      );
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3));*/

    /*rtc_sleep((uint8_t) 5);
    tty_colored(2, "OK");*/

    keyboard_leds_set(true, true, false);
    keyboard_init(11);

    while(1) {
        //enum KEYCODE k = KEY_UNKNOWN;

        tty_writeString("\n > ");

        enum KEYCODE key = getKey();
        char key_ascii   = keyboard_key2ascii(key);

        tty_writeString(key_ascii);
    }
}