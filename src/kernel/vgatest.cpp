#include "kernel/tty.h"
#include "drivers/vga.h"
#include "drivers/pit.h"
#include "kernel/cursor.h"
#include <stddef.h>

using namespace Kernel;
using namespace Kernel::TTY;
using namespace Kernel::Cursor;

#ifndef __E_ARCH_X64
    #define __E_ARCH_X32
#endif

extern "C" void kernel_main(/*multiboot_info* __boot_info*/ void) {
    tty_init();

    /*asm("mov ax,1112h");
    asm("xor bl,bl");
    asm("int 10h");*/

    cursor_disable();

    colored(3, "CubeBox OS: kernel:v0.0.1.0a\n");
    writeString("https://github.com/COOKIE-1816/cubebox-os\n");
    writeString("http://czechcookie.euweb.cz/projects/cubebox-os\n\n");

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
}