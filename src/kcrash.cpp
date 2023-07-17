#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/cursor.h"
#include "drivers/keyboard.h"
#include "drivers/buzzer.h"
//#include "drivers/pit.h"

using namespace VGA;
using namespace Kernel::TTY;
using namespace Kernel::Cursor;
//using namespace PIT;

extern "C" void kcrash(void) {
    //tty_init();
    //pit_init();

    buzzer_makeSound(1000);

    writeString("\n\n ===== ! KERNEL CRASH ! =====\n");
    writeString("Kernel crashed and cannot restore itself.\n");
    writeString("You can leave it running and use debug tools for diagnosis purposes, or just try rebooting.\n\n");

    writeString("System is halted now.");

    asm("cli");
    while(1) {
        kbd_setLeds(0, 0, 0);
        kbd_setLeds(0, 1, 0);
    }
}