#ifndef _CB_IDE_H_
#define _CB_IDE_H_

#define IDE_ATA        0x00
#define IDE_ATAPI      0x01
 
#include "drivers/ata/atapi.h"

unsigned char ide_read(unsigned char channel, unsigned char reg);
void ide_write(unsigned char channel, unsigned char reg, unsigned char data);

void ide_readBuffer(            unsigned char __channel, 
                                unsigned char __reg, 
                                unsigned int  __buffer,
                                unsigned int  __quads);

unsigned char ide_polling(unsigned char channel, unsigned int advanced_check);
unsigned char ide_printErr(unsigned int drive, unsigned char err);

void ide_init(                  unsigned int BAR0, 
                                unsigned int BAR1, 
                                unsigned int BAR2,
                                unsigned int BAR3,
                                unsigned int BAR4);

unsigned char ide_ata_access(   unsigned char direction, 
                                unsigned char drive,
                                unsigned int lba, 
                                unsigned char numsects,
                                unsigned short selector, 
                                unsigned int edi);

void ide_readSectors(           unsigned char drive, 
                                unsigned char numsects, 
                                unsigned int lba,
                                unsigned short es, 
                                unsigned int edi);

void ide_writeSectors(          unsigned char drive, 
                                unsigned char numsects, 
                                unsigned int lba,
                                unsigned short es, 
                                unsigned int edi);

void ide_atapi_eject(unsigned char drive);

#endif