#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/cursor.h"
#include "drivers/keyboard.h"
#include "drivers/buzzer.h"
#include "kernel/system.h"
#include "kernel/error.h"
//#include "drivers/pit.h"

using namespace VGA;
using namespace Kernel;
using namespace Kernel::TTY;
using namespace Kernel::Cursor;
//using namespace PIT;


uint8_t blinkingLightRed = 0x8C;

extern "C" void kpanic(String __error) {
    buzzer_makeSound(1000);

    writeString("\n\n ===== [ KERNEL PANIC ] =====\n");
    colored(blinkingLightRed, "Kernel panic. Kernel stopped ( kmain.cpp: kernel_main() ).\n");

    setColor(15);

    writeString("L.K. Error (??) |  "); 
    writeString(__error);
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

extern "C" void kcrash(void) {
    char* err = getError();

    if(!err) {
        err = ((char*) "KERNEL_ERR_UNKNOWN");
    }

    kpanic((String) err);
}