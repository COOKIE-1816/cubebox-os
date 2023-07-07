#include "kernel/kdrivers.h"
#include "kernel/tty.h"
#include "drivers/vga.h"
#include "stringt.h"
#include "stddef.h"

using namespace VGA;
using namespace Kernel::TTY;

size_t _line;

Kernel::Kdrivers::kdriver driversloaded[1024];
bool driversaddressesusage[1024];

void Kernel::Kdrivers::statusMsg_create(kdriver __drv) {
    _line = getRow();
    String driver_name = __drv.name;

    writeString("      Load driver: ");
    colored(15, driver_name);
    writeString("\n");

    Kernel::Kdrivers::statusMsg_status(KDRIVERS_PENDING);

    uint8_t ec = entryColor(VGA_COLOR_WHITE, VGA_COLOR_MAGENTA);
    putEntryAt('D', ec, 0, _line);
}

void Kernel::Kdrivers::statusMsg_status(/*kdriver */ const int __status) {
    char* status;
    //enum VGA_COLOR color;
    enum vga_color color;

    switch (__status) {
        case KDRIVERS_PENDING:
            status = "WAIT";
            color = VGA_COLOR_BLUE; //TODO: Fix the color-related glitch and make this yellow

            break;
        
        case KDRIVERS_OK:
            status = "OKAY";
            color = VGA_COLOR_GREEN;

            break;
        
        case KDRIVERS_FAIL:
        default:
            status = "FAIL";
            color = VGA_COLOR_RED;

            break;
    }

    uint8_t ec = entryColor(VGA_COLOR_WHITE, color);

    for(size_t i = 0; i < 4; i++) {
        putEntryAt(status[i], ec, i + 1, _line);
    }

    ec = entryColor(VGA_COLOR_WHITE, VGA_COLOR_MAGENTA);
    putEntryAt('D', ec, 0, _line);

    /*if(__status != KDRIVERS_PENDING)
        tty_writeString("\n");*/
}

void Kernel::Kdrivers::init() {
    for(int i = 0; i < 1024; i++) {
        driversaddressesusage[i] = false;
    }

    /*tty_writeString("OK:   Initialize module ");
    tty_colored(15, "kdriver");
    tty_writeString(" (static).\n");*/
}