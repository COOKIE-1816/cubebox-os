#include "kernel/tty.h"
#include "drivers/vga.h"
#include <stddef.h>

#ifndef __E_VGATEST
    #include "kernel/interrupt/idt.h"
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


    using namespace Kernel::IRQ;
    using namespace Kernel::IDT;
    using namespace Kernel::GDT;
#endif

using namespace Kernel;
using namespace Kernel::TTY;

#ifndef __E_ARCH_X64
    #define __E_ARCH_X32
#endif

/*void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        writeString("-");
}*/

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

extern "C" void kernel_main(/*multiboot_info* __boot_info*/ void) {
    tty_init();

    colored(3, "CubeBox OS: kernel:v0.0.1.0a\n");
    writeString("https://github.com/COOKIE-1816/cubebox-os\n");
    writeString("http://czechcookie.euweb.cz/projects/cubebox-os\n\n");

    #ifndef __E_VGATEST
    gdt_install();
    idt_init();
    irq_init();

    Kdrivers::init();

    kbd_init();
    #endif

    #if defined(__E_VGATEST)
        writeString("VGA Driver testing.\n\n");

        static String nums[16] = {
            "00", "01", "02", "03",
            "04", "05", "06", "07",
            "08", "09", "0a", "0b",
            "0c", "0d", "0e", "0f"
        };

        // Foregrounds
        for(int i = 0; i < 16; i++) {

            colored(i, nums[i]);
        }


    #endif
}