#ifndef _CB_FLOPPY_H_
#define _CB_FLOPPY_H_

#define FLOPPY_144_SECTORS_PER_TRACK 18

#include <stdint.h>
#include "drivers/floppy/drivetypes.h"



extern void floppy_lbaToChs(uint32_t __lba, uint16_t* __cylinder, uint16_t* __head, uint16_t* __sector);
extern void floppy_detect();
extern void floppy_writeCmd(int base, char cmd);
extern unsigned char floppy_readData(int base);

#endif