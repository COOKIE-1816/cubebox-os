#include "kernel/interrupt/idt.h"
#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/gdt.h"
#include "drivers/keyboard.h"
#include "kernel/common.h"
#include "stringt.h"
#include "drivers/rtc.h"
#include "kernel/kdrivers.h"
#include "drivers/timer.h"
#include "drivers/pic.h"
#include "drivers/acpi.h"
#include "kernel/system.h"
#include "kernel/interrupt/irq.h"
#include <stddef.h>

#ifndef __E_ARCH_X64
    #define __E_ARCH_X32
#endif

void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        tty_writeString("-");
}

void kernel_initializeKernelParticipals() {
    tty_initialize();
    
    gdt_init();
    gdt_install();
    
    idt_init();

    kdriver_init();
}

unsigned char* stringMem(size_t __size) {
    unsigned char* memoryPtr = (unsigned char*) 0;
    unsigned char* currentPtr = memoryPtr;

    while (__size > 0) {
        *currentPtr = 0;
        currentPtr++;
        __size--;
    }

    return memoryPtr;
}

/*enum KEYCODE getKey() {
    enum KEYCODE k = KEY_UNKNOWN;

    while(k == KEY_UNKNOWN)
        k = keyboard_getLastKey();

    tty_writeString("Key pressed.");
    
    keyboard_discardLastKey();
    return k;
}*/



/*void commandLine() {
    char* buff;

    while(1) {
        tty_writeString("\n> ");

        enum KEYCODE key = getKey();
        if (key == KEY_KP_ENTER)
            continue;

        char key_ascii = keyboard_key2ascii(key);
        tty_putChar(key_ascii);
    }
}*/

void kernel_main(/*multiboot_info* __boot_info*/ void) {
    kernel_initializeKernelParticipals();

    //tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n\n");
    tty_colored(3, "CubeBox OS: kernel:v0.0.1.0a\n\n");

    pic_init();
    kbd_init();
    //acpi_init();

    /*keyboard_init(11);
    keyboard_leds_set(true, false, false);*/

    //shutdown();

    //ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);

    //floppy_init();

    //commandLine();
}