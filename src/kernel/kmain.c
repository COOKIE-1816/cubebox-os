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
#include "text_ui/shapes.h"

#ifndef __E_ARCH_X64
    #define __E_ARCH_X32
#endif

void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        tty_writeString("-");
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

void kernel_main(/*multiboot_info* __boot_info*/ void) {
    tty_initialize();
    
    //tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n\n");
    tty_colored(3, "CubeBox OS: kernel:v0.0.1.0a\n");
    tty_writeString("https://github.com/COOKIE-1816/cubebox-os\n");
    tty_writeString("http://czechcookie.euweb.cz/projects/cubebox-os\n\n");

    gdt_install();
    idt_init();

    kdriver_init();

    kbd_init();
}