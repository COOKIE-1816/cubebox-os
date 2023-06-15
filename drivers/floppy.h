#ifndef _CB_FLOPPY_H_
#define _CB_FLOPPY_H_

#define FLOPPY_144_SECTORS_PER_TRACK 18

#include <stdint.h>
#include "drivers/floppy/drivetypes.h"

enum floppy_registers {
    REG_STATUS_A        = 0x3F0,
    REG_STATUS_B        = 0x3F1,
    REG_DIGITAL_OUT     = 0x3F2,
    REG_TAPE_DRIVE      = 0x3F3,
    REG_MAIN_STATUS     = 0x3F4,
    REG_DATARATE_SEL    = 0x3F4,
    REG_DATA_FIFO       = 0x3F5,
    REG_DIGITAL_IN      = 0x3F7,
    REG_CONFIG_CONTROL  = 0x3F7,
};

enum floppy_commands {
    CMD_READ_TRACK      = 2,
    CMD_SPECIFY         = 3,
    CMD_SENSE_STATUS    = 4,
    CMD_WRITE_DATA      = 5,
    CMD_READ_DATA       = 6,
    CMD_RECABLIBRATE    = 7,
    CMD_SENSE_INTERRUPT = 8,
    CMD_WRITE_DELETE    = 9,
    CMD_READ_ID         = 10,
    CMD_READ_DELETE     = 12,
    CMD_FORMAT_TRACK    = 13,
    CMD_DUMPREG         = 14,
    CMD_SEEK            = 15,
    CMD_VERSION         = 16,
    CMD_SCAN_EQUAL      = 17,
    CMD_PREPENDICULAR   = 18,
    CMD_CONFIGURE       = 19,
    CMD_LOCK            = 20,
    CMD_VERIFY          = 22,
    CMD_SCAN_LOW_EQUAL  = 25,
    CMD_SCAN_HIGH_EQUAL = 29
};

extern void floppy_lbaToChs(uint32_t __lba, uint16_t* __cylinder, uint16_t* __head, uint16_t* __sector);
extern void floppy_detect();
extern void floppy_writeCmd(int base, char cmd);
extern unsigned char floppy_readData(int base);

#endif