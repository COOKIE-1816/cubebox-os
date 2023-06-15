#include "kernel/kdrivers.h"
#include "kernel/tty.h"
#include "drivers/vga.h"
#include "stringt.h"
#include "stddef.h"

size_t _line;

kdriver driversloaded[1024];
bool driversaddressesusage[1024];

void kdriver_statusMsg_create(kdriver __drv) {
    _line = tty_getRow();
    String driver_name = __drv.name;

    tty_writeString("     Load driver: ");
    tty_colored(15, driver_name);
    tty_writeString("\n");

    kdriver_statusMsg_status(KDRIVERS_PENDING);
}

void kdriver_statusMsg_status(/*kdriver */ const int __status) {
    char* status;
    //enum VGA_COLOR color;
    int color;

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

    uint8_t ec = vga_entryColor(VGA_COLOR_WHITE, color);

    for(size_t i = 0; i < 4; i++) {
        tty_putEntryAt(status[i], ec, i, _line);
    }

    /*if(__status != KDRIVERS_PENDING)
        tty_writeString("\n");*/
}

void kdriver_init() {
    for(int i = 0; i < 1024; i++) {
        driversaddressesusage[i] = false;
    }

    /*tty_writeString("OK:   Initialize module ");
    tty_colored(15, "kdriver");
    tty_writeString(" (static).\n");*/
}