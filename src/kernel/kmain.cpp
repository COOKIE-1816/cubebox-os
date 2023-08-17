#include "kernel/kernel.h"
#include "kernel/terminal.h"

void printVersion() {
    Terminal::wstring("Kernel version: ");
    Terminal::wstring(kernel_version);

    #if KDEVSTAGE_STRING != "stable"
        Terminal::wstring(KDEVSTAGE_STRING);
    #endif

    Terminal::wstring("\n");
}

extern "C" void kmain(void) {
    Terminal::init();

    Terminal::setColor(0x02); // Green text
    Terminal::wstring("CubeBox OS!\n\n");

    Terminal::resetColor();
    printVersion();
}