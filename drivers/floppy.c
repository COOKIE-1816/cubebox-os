#include "drivers/floppy.h"
#include "kernel/common.h"
#include "kernel/tty.h"
#include "drivers/floppy/drivetypes.h"

unsigned _drives;

inline void floppy_lbaToChs(uint32_t __lba, uint16_t* __cylinder, uint16_t* __head, uint16_t* __sector) {
    *__cylinder = __lba / (2 * FLOPPY_144_SECTORS_PER_TRACK);
    *__head     = ((__lba % (2 * FLOPPY_144_SECTORS_PER_TRACK)) / FLOPPY_144_SECTORS_PER_TRACK);
    *__sector   = ((__lba % (2 * FLOPPY_144_SECTORS_PER_TRACK)) % FLOPPY_144_SECTORS_PER_TRACK);
}

inline void floppy_detect() {
    outb(0x70, 0x10);
    _drives = inb(0x71);

    tty_writeString("    -> Floppy drive 0: ");
    tty_writeString(floppy_driveTypes[_drives >> 4]);

    tty_writeString("    -> Floppy drive 1: ");
    tty_writeString(floppy_driveTypes[_drives & 0xf]);
}

inline void floppy_writeCmd(int base, char cmd) {
    for(int i = 0; i < 600; i++) {}
}