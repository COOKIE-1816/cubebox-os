#ifndef _CB_FLOPPY_H_
#define _CB_FLOPPY_H_

#define FLOPPY_144_SECTORS_PER_TRACK 18

#include <stdint.h>



extern void floppy_lbaToChs(uint32_t __lba, uint16_t* __cylinder, uint16_t* __head, uint16_t* __sector);
extern void floppy_detect();
//extern void floppy_writeCmd(int base, char cmd);
//extern unsigned char floppy_readData(int base);
//extern void floppy_checkInterrupt(int __base, int* __st0, int* __cyl);
//extern int floppy_calibrate(int base);
//extern int floppy_reset(int base);
//extern void floppy_motor(int base, int onoff);
//extern void floppy_motor_kill(int base);
//extern void floppy_timer();
extern void floppy_init();

#endif