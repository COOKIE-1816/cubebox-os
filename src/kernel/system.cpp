#include "drivers/acpi.h"
#include "kernel/system.h"
#include "kernel/common.h"
#include "kernel/tty.h"

using namespace Kernel::TTY;

void _fail() {
    colored(3, "\nKernel was unable to shutdown or reset this machine. You can try shutting down or reseting the machine manually.\n");
    writeString("CPU halted.");
}

void _warn() {
    colored(15, "WARNING: System is going to shut down now!\n");
}

void shutdown() {
    _warn();

    /*if(SCI_EN != 0) {
        acpi_enable();

        outb((unsigned int) PM1a_CNT, SLP_TYPa | SLP_EN );

        if ( PM1b_CNT != 0 )
            outb((unsigned int) PM1b_CNT, SLP_TYPb | SLP_EN );
    }*/

    acpi_shutdown();

    // On emulators, use emulator-specific register to send shutdown command
    outb(0xB004, (uint8_t) 0x2000); // Shutdown QEMU < 2.0, BOCHS
    outb(0x604,  (uint8_t) 0x2000); // Shutdown QEMU >= 2.0
    outb(0x4004, (uint8_t) 0x3400); // Shutdown VirtualBox

    _fail();
}

void reboot() {
    _warn();

    uint8_t good = 0x02;
    
    while (good & 0x02)
        good = inb(0x64);

    outb(0x64, 0xFE);

    _fail();
}