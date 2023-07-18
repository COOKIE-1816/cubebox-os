#include "drivers/acpi.h"
#include "kernel/system.h"
#include "kernel/common.h"
#include "kernel/tty.h"
#include "kernel/panic.h"

//using namespace Kernel;
using namespace Kernel::TTY;
using namespace ACPI;

void _fail() {
    kpanic("KERNEL_ERR_POWER_OFF_FAIL");
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

    

    // On emulators, use emulator-specific register to send shutdown command
    outb(0xB004, (uint8_t) 0x2000); // Shutdown QEMU < 2.0, BOCHS
    outb(0x604,  (uint8_t) 0x2000); // Shutdown QEMU >= 2.0
    outb(0x4004, (uint8_t) 0x3400); // Shutdown VirtualBox

    acpi_shutdown();

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

volatile uint32_t CountDown;

void Kernel::System::sleep(uint32_t __ms) {
    CountDown = __ms;
    while (CountDown > 0);
}