#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/gdt/gdt.h"
#include "drivers/keyboard.h"
#include "kernel/common.h"
#include "stringt.h"
#include "drivers/rtc.h"
#include "kernel/kdrivers.h"
#include "drivers/timer.h"
#include "drivers/pic.h"
#include "drivers/acpi.h"
#include "kernel/system.h"
#include <stddef.h>

void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        tty_writeString("-");
}

void kernel_initializeKernelParticipals() {
    tty_initialize();
    kdriver_init();
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

void sh(String c) {
    tty_writeString(c);
}



void commandLine() {
    while(1) {
        //enum KEYCODE k = KEY_UNKNOWN;

        tty_writeString("\n> ");

        enum KEYCODE key = getKey();
        if (key == KEY_KP_ENTER)
            continue;

        char key_ascii   = keyboard_key2ascii(key);

        tty_writeString(key_ascii);
    }

    sh();
}

void kernel_main(/*multiboot_info* __boot_info*/ void) {
    kernel_initializeKernelParticipals();

    //tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n\n");
    tty_colored(3, "CubeBox OS: kernel:v0.0.1.0a\n\n");

    pic_init();
    //acpi_init();

    keyboard_init(33);
    keyboard_leds_set(true, false, false);

    //shutdown();

    //ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);

    //floppy_init();

    commandLine();
}