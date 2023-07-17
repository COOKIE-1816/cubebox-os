#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/cursor.h"
#include "drivers/keyboard.h"
#include "drivers/buzzer.h"
#include "kernel/system.h"
//#include "drivers/pit.h"

using namespace VGA;
using namespace Kernel::TTY;
using namespace Kernel::Cursor;
//using namespace PIT;

uint8_t blinkingLightRed = 0x8C;

extern "C" void kcrash(void) {
    //tty_init();
    //pit_init();

    buzzer_makeSound(1000);

    writeString("\n\n ===== [ KERNEL PANIC ] =====\n");
    colored(blinkingLightRed, "Kernel panic. Kernel stopped ( kmain.cpp: kernel_main() ).\n");

    setColor(15);

    writeString("L.K. Error      |  "); 
    writeString("\n");
    writeString("Memory dumpfile |  "); 
    writeString("\n");
    writeString("Kernel          |  "); 
    writeString(KERNEL_VERSION_STRING); 
    writeString("\n");
    writeString("Halting CPU...\n");

    setColor(7);

    writeString(" ============================");


    asm("cli");
    while(1) {
        kbd_setLeds(0, 0, 0);
        kbd_setLeds(0, 1, 0);
    }
}