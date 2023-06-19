#include "drivers/ide.h"
#include "drivers/ata/atadefs.h"
#include "kernel/common.h"
#include "kernel/tty.h"
#include "drivers/rtc.h"

unsigned char ide_buf[2048] = {0};
volatile unsigned static char ide_irq_invoked = 0;

struct ide_channelRegisters {
   unsigned short base;
   unsigned short ctrl;
   unsigned short bmide;
   unsigned char  nIEN;
} channels[2];

struct ide_device {
   unsigned char  Reserved;
   unsigned char  Channel;
   unsigned char  Drive;
   unsigned short Type;
   unsigned short Signature;
   unsigned short Capabilities;
   unsigned int   CommandSets;
   unsigned int   Size;
   unsigned char  Model[41];
} ide_devices[4];

//ide_read(channel, ATA_REG_STATUS);
 
unsigned char ide_read(unsigned char channel, unsigned char reg) {
    unsigned char result;

    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);

    if (reg < 0x08)
        result = inb(channels[channel].base + reg - 0x00);
    else if (reg < 0x0C)
        result = inb(channels[channel].base  + reg - 0x06);
    else if (reg < 0x0E)
        result = inb(channels[channel].ctrl  + reg - 0x0A);
    else if (reg < 0x16)
        result = inb(channels[channel].bmide + reg - 0x0E);

    if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);

   return result;
}

void ide_write(unsigned char channel, unsigned char reg, unsigned char data) {
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);

    if (reg < 0x08)
        outb(channels[channel].base  + reg - 0x00, data);
    else if (reg < 0x0C)
        outb(channels[channel].base  + reg - 0x06, data);
    else if (reg < 0x0E)
        outb(channels[channel].ctrl  + reg - 0x0A, data);
    else if (reg < 0x16)
        outb(channels[channel].bmide + reg - 0x0E, data);
        
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

void ide_readBuffer(    unsigned char __channel, 
                        unsigned char __reg, 
                        unsigned int  __buffer,
                        unsigned int  __quads) {

    //! THIS CONTAINS A SERVE BUG!!!

    if (__reg > 0x07 && __reg < 0x0C)
        ide_write(__channel, ATA_REG_CONTROL, 0x80 | channels[__channel].nIEN);

    asm("pushw %es; movw %ds, %ax; movw %ax, %es");

    if (__reg < 0x08)
        insl(channels[__channel].base  + __reg - 0x00, __buffer, __quads);
    else if (__reg < 0x0C)
        insl(channels[__channel].base  + __reg - 0x06, __buffer, __quads);
    else if (__reg < 0x0E)
        insl(channels[__channel].ctrl  + __reg - 0x0A, __buffer, __quads);
    else if (__reg < 0x16)
        insl(channels[__channel].bmide + __reg - 0x0E, __buffer, __quads);

    asm("popw %es;");

    if (__reg > 0x07 && __reg < 0x0C)
        ide_write(__channel, ATA_REG_CONTROL, channels[__channel].nIEN);
}

unsigned char ide_polling(unsigned char channel, unsigned int advanced_check) {
    for(int i = 0; i < 4; i++)
        ide_read(channel, ATA_REG_ALTSTATUS);
    
    while(ide_read(channel, ATA_REG_STATUS) & ATA_SR_BUSY);
    
    if (advanced_check) {
        unsigned char state = ide_read(channel, ATA_REG_STATUS);
        
        if (state & ATA_SR_ERROR)
            return 2; // Error.

        if (state & ATA_SR_DRIVE_WRITE_FAULT)
            return 1; // Device Fault.
    
        if ((state & ATA_SR_DRIVE_REQUEST_READY) == 0)
            return 3; // DRQ should be set
    }
    
    return 0; // No Error.
}

unsigned char ide_printErr(unsigned int drive, unsigned char err) {
    if (err == 0)
        return err;

    if(err == 1) {
        tty_writeString("IDE: Err: Device Fault\n");
        err = 19;
    } else if (err == 2) {
        unsigned char st = ide_read(ide_devices[drive].Channel, ATA_REG_ERROR);

        if (st & ATA_ERROR_NO_ADDRESS_MARK) {
            tty_writeString("IDE: Err: No Address Mark Found\n");
            err = 7;
        }
        
        if (st & ATA_ERROR_TRACK0_NOT_FOUND) {
            tty_writeString("IDE: Err: No Media or Media Error\n");
            err = 3;
        }

        if (st & ATA_ERROR_ABROT) {
            tty_writeString("IDE: Err: Command Aborted\n");
            err = 20;
        }

        if (st & ATA_ERROR_MEDIA_CHANGE_REQUEST) {
            tty_writeString("IDE: Err: No Media or Media Error\n");
            err = 3;
        }
        
        if (st & ATA_ERROR_ID_MARK_NOT_FOUND) {
            tty_writeString("IDE: Err: ID mark not Found\n");
            err = 21;
        }

        if (st & ATA_ERROR_MEDIA_CHANGE) {
            tty_writeString("IDE: Err: No Media or Media Error\n");
            err = 3;
        }

        if (st & ATA_ERROR_UNCORRECTABLE) {
            tty_writeString("IDE: Err: Uncorrectable Data Error\n");
            err = 22;
        }

        if (st & ATA_ERROR_BAD_BLOCK) {
            tty_writeString("IDE: Err: Bad Sectors\n");
            err = 13;
        }
    } else if (err == 3) {
        tty_writeString("IDE: Err: Reads Nothing\n");
        err = 23;
    } else  if (err == 4) {
        tty_writeString("IDE: Err: Write Protected\n");
        err = 8;
    }

    tty_writeString("  -> Device: ");

    tty_writeString(
        (const char *[]){
            "Primary", 
            "Secondary"
        }[ide_devices[drive].Channel]
    );

    tty_writeString(" ");

    tty_writeString(
        (const char *[]){
            "Master", 
            "Salve"
        }[ide_devices[drive].Drive]
    );

    tty_writeString(" - ");
    tty_writeString(ide_devices[drive].Model);
    tty_writeString("\n");
    
    return err;
}

void ide_init(  unsigned int BAR0, 
                unsigned int BAR1, 
                unsigned int BAR2,
                unsigned int BAR3,
                unsigned int BAR4) {

    int j, k, count = 0;
 
    channels[ATA_PRIMARY  ].base  = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
    channels[ATA_PRIMARY  ].ctrl  = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
    channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
    channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
    channels[ATA_PRIMARY  ].bmide = (BAR4 & 0xFFFFFFFC) + 0;
    channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8;

    ide_write(ATA_PRIMARY  , ATA_REG_CONTROL, 2);
    ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);

    for (int i = 0; i < 2; i++)
        for (j = 0; j < 2; j++) {
            unsigned char err = 0, type = IDE_ATA, status;
            ide_devices[count].Reserved = 0;
    
            ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
            //sleep(1);
            rtc_sleep(1);
    
            ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
            //sleep(1);
            rtc_sleep(1);
            
            if(ide_read(i, ATA_REG_STATUS) == 0)
                continue;
    
            while(1) {
                status = ide_read(i, ATA_REG_STATUS);

                if((status & ATA_SR_ERROR)) {
                    err = 1; 
                    break;
                }

                if(!(status & ATA_SR_BUSY) && (status & ATA_SR_DRIVE_REQUEST_READY)) 
                    break;
            }
    
            if (err != 0) {
                unsigned char cl = ide_read(i, ATA_REG_LBA1);
                unsigned char ch = ide_read(i, ATA_REG_LBA2);
    
                if (cl == 0x14 && ch ==0xEB) {
                    type = IDE_ATAPI;
                } else if (cl == 0x69 && ch == 0x96) {
                    type = IDE_ATAPI;
                } else {
                    continue;
                }
    
                ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
                //sleep(1);
                rtc_sleep(1);
            }
    
            ide_readBuffer(i, ATA_REG_DATA, (unsigned int) ide_buf, 128);
    
            ide_devices[count].Reserved     = 1;
            ide_devices[count].Type         = type;
            ide_devices[count].Channel      = i;
            ide_devices[count].Drive        = j;
            ide_devices[count].Signature    = *((unsigned short *)(ide_buf + ATA_IDENTIFY_DEVICETYPE));
            ide_devices[count].Capabilities = *((unsigned short *)(ide_buf + ATA_IDENTIFY_CAPABILITIES));
            ide_devices[count].CommandSets  = *((unsigned int *)  (ide_buf + ATA_IDENTIFY_COMMANDSETS));
    
            if(ide_devices[count].CommandSets & (1 << 26)) {
                ide_devices[count].Size   = *((unsigned int *)(ide_buf + ATA_IDENTIFY_MAX_LBA_EXT));
            } else {
                ide_devices[count].Size   = *((unsigned int *)(ide_buf + ATA_IDENTIFY_MAX_LBA));
            }
    
            for(k = 0; k < 40; k += 2) {
                ide_devices[count].Model[k]     = ide_buf[ATA_IDENTIFY_MODEL + k + 1];
                ide_devices[count].Model[k + 1] = ide_buf[ATA_IDENTIFY_MODEL + k];
            }

            ide_devices[count].Model[40] = 0;
            count++;
        }
    
    for (int i = 0; i < 4; i++)
        if (ide_devices[i].Reserved == 1) {
            tty_writeString("IDE: Found ");
            tty_writeString(
                (const char *[]) {
                    "ATA", 
                    "ATAPI"
                }[ide_devices[i].Type]
            );
            tty_writeString(".\n");

            // TODO: Make it print capacity.
        }
}

   /* ATA/ATAPI Read/Write Modes:
    * ++++++++++++++++++++++++++++++++
    *  Addressing Modes:
    *  ================
    *   - LBA28 Mode.     (+)
    *   - LBA48 Mode.     (+)
    *   - CHS.            (+)
    *  Reading Modes:
    *  ================
    *   - PIO Modes (0 : 6)       (+) // Slower than DMA, but not a problem.
    *   - Single Word DMA Modes (0, 1, 2).
    *   - Double Word DMA Modes (0, 1, 2).
    *   - Ultra DMA Modes (0 : 6).
    *  Polling Modes:
    *  ================
    *   - IRQs
    *   - Polling Status   (+) // Suitable for Singletasking   
    */

unsigned char ide_ata_access(   unsigned char direction, 
                                unsigned char drive,
                                unsigned int lba, 
                                unsigned char numsects,
                                unsigned short selector, 
                                unsigned int edi){
    
    unsigned char   lba_mode,
                    dma, 
                    cmd;
    unsigned char lba_io[6];
    unsigned int  channel   = ide_devices[drive].Channel;
    unsigned int  slavebit  = ide_devices[drive].Drive;
    unsigned int  bus       = channels[channel].base;
    unsigned int  words     = 256;
    unsigned short  cyl, 
                    i;
    unsigned char   head, 
                    sect, 
                    err;

    ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = (ide_irq_invoked = 0x0) + 0x02);

    if (lba >= 0x10000000) {
        lba_mode  = 2;
        lba_io[0] = (lba & 0x000000FF) >> 0;
        lba_io[1] = (lba & 0x0000FF00) >> 8;
        lba_io[2] = (lba & 0x00FF0000) >> 16;
        lba_io[3] = (lba & 0xFF000000) >> 24;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = 0;
    } else if (ide_devices[drive].Capabilities & 0x200)  {
        lba_mode  = 1;
        lba_io[0] = (lba & 0x00000FF) >> 0;
        lba_io[1] = (lba & 0x000FF00) >> 8;
        lba_io[2] = (lba & 0x0FF0000) >> 16;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (lba & 0xF000000) >> 24;
    } else {
        lba_mode  = 0;
        sect      = (lba % 63) + 1;
        cyl       = (lba + 1  - sect) / (16 * 63);
        lba_io[0] = sect;
        lba_io[1] = (cyl >> 0) & 0xFF;
        lba_io[2] = (cyl >> 8) & 0xFF;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (lba + 1  - sect) % (16 * 63) / (63);
    }

    dma = 0;

    while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BUSY);

    if (lba_mode == 0) {
        ide_write(channel, ATA_REG_HDDEVSEL, 0xA0 | (slavebit << 4) | head);
    } else {
        ide_write(channel, ATA_REG_HDDEVSEL, 0xE0 | (slavebit << 4) | head);
    }

    if (lba_mode == 2) {
        ide_write(channel, ATA_REG_SECCOUNT1,   0);
        ide_write(channel, ATA_REG_LBA3,   lba_io[3]);
        ide_write(channel, ATA_REG_LBA4,   lba_io[4]);
        ide_write(channel, ATA_REG_LBA5,   lba_io[5]);
    }

    ide_write(channel, ATA_REG_SECCOUNT0,   numsects);
    ide_write(channel, ATA_REG_LBA0,        lba_io[0]);
    ide_write(channel, ATA_REG_LBA1,        lba_io[1]);
    ide_write(channel, ATA_REG_LBA2,        lba_io[2]);

    if (lba_mode == 0 && dma == 0 && direction == 0) 
        cmd = ATA_CMD_READ_PIO;
    if (lba_mode == 1 && dma == 0 && direction == 0) 
        cmd = ATA_CMD_READ_PIO;   
    if (lba_mode == 2 && dma == 0 && direction == 0) 
        cmd = ATA_CMD_READ_PIO_EXT;   
    if (lba_mode == 0 && dma == 1 && direction == 0) 
        cmd = ATA_CMD_READ_DMA;
    if (lba_mode == 1 && dma == 1 && direction == 0)
        cmd = ATA_CMD_READ_DMA;
    if (lba_mode == 2 && dma == 1 && direction == 0) 
        cmd = ATA_CMD_READ_DMA_EXT;
    if (lba_mode == 0 && dma == 0 && direction == 1) 
        cmd = ATA_CMD_WRITE_PIO;
    if (lba_mode == 1 && dma == 0 && direction == 1) 
        cmd = ATA_CMD_WRITE_PIO;
    if (lba_mode == 2 && dma == 0 && direction == 1) 
        cmd = ATA_CMD_WRITE_PIO_EXT;
    if (lba_mode == 0 && dma == 1 && direction == 1) 
        cmd = ATA_CMD_WRITE_DMA;
    if (lba_mode == 1 && dma == 1 && direction == 1) 
        cmd = ATA_CMD_WRITE_DMA;
    if (lba_mode == 2 && dma == 1 && direction == 1)
        cmd = ATA_CMD_WRITE_DMA_EXT;

    ide_write(channel, ATA_REG_COMMAND, cmd);

    if (dma)
        // TODO: Complete DMA R/W
        if (direction == 0);
            // DMA Read.
        else;
            // DMA Write.
    else
        if (direction == 0)
            // PIO Read.
        for (i = 0; i < numsects; i++) {
            if (err = ide_polling(channel, 1))
                return err;

            asm("pushw %es");
            asm("mov %%ax, %%es" : : "a"(selector));
            asm("rep insw" : : "c"(words), "d"(bus), "D"(edi));
            asm("popw %es");

            edi += (words*2);
        } else {
        // PIO Write.

            for (i = 0; i < numsects; i++) {
                ide_polling(channel, 0);

                asm("pushw %ds");
                asm("mov %%ax, %%ds"::"a"(selector));
                asm("rep outsw"::"c"(words), "d"(bus), "S"(edi));
                asm("popw %ds");

                edi += (words*2);
            }

            ide_write(channel, ATA_REG_COMMAND, (char []) {
                ATA_CMD_CACHE_FLUSH,
                ATA_CMD_CACHE_FLUSH,
                ATA_CMD_CACHE_FLUSH_EXT
            }[lba_mode]);

            ide_polling(channel, 0);
        }
    
   return 0;
} 

void ide_wait_irq() {
    while (!ide_irq_invoked);
    ide_irq_invoked = 0;
}

void ide_irq() {
    ide_irq_invoked = 1;
}

unsigned char ide_atapi_read(   unsigned char drive, 
                                unsigned int  lba,
                                unsigned char numsects,
                                unsigned short selector, 
                                unsigned int edi) {

    unsigned int   channel  = ide_devices[drive].Channel;
    unsigned int   slavebit = ide_devices[drive].Drive;
    unsigned int   bus      = channels[channel].base;
    unsigned int   words    = 1024;
    unsigned char  err;

    int i;

    ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = ide_irq_invoked = 0x0);

    atapi_packet[ 0] = /*ATAPI_CMD_READ*/ 0x28;
    atapi_packet[ 1] = 0x0;
    atapi_packet[ 2] = (lba >> 24) & 0xFF;
    atapi_packet[ 3] = (lba >> 16) & 0xFF;
    atapi_packet[ 4] = (lba >> 8) & 0xFF;
    atapi_packet[ 5] = (lba >> 0) & 0xFF;
    atapi_packet[ 6] = 0x0;
    atapi_packet[ 7] = 0x0;
    atapi_packet[ 8] = 0x0;
    atapi_packet[ 9] = numsects;
    atapi_packet[10] = 0x0;
    atapi_packet[11] = 0x0;

    ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);

    for(int i = 0; i < 4; i++)
        ide_read(channel, ATA_REG_ALTSTATUS);

    ide_write(channel, ATA_REG_FEATURES, 0);

    ide_write(channel, ATA_REG_LBA1, (words * 2) & 0xFF);
    ide_write(channel, ATA_REG_LBA2, (words * 2) >> 8);

    ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);
 
    if (err = ide_polling(channel, 1))
        return err;
 
    asm("rep   outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));

    for (i = 0; i < numsects; i++) {
        ide_wait_irq();

        if (err = ide_polling(channel, 1))
            return err;

        asm("pushw %es");
        asm("mov %%ax, %%es"::"a"(selector));
        asm("rep insw"::"c"(words), "d"(bus), "D"(edi));
        asm("popw %es");

        edi += (words * 2);
   }

   ide_wait_irq();
 
   while (ide_read(channel, ATA_REG_STATUS) & (ATA_SR_BUSY | ATA_SR_DRIVE_REQUEST_READY));
   return 0;
}

int* package[];

void ide_readSectors(   unsigned char drive, 
                        unsigned char numsects, 
                        unsigned int lba,
                        unsigned short es, 
                        unsigned int edi) {
 
    if (drive > 3 || ide_devices[drive].Reserved == 0) {
        package[0] = 0x1;
    } else if (((lba + numsects) > ide_devices[drive].Size) && (ide_devices[drive].Type == IDE_ATA)) {
        package[0] = 0x2;
    } else {
        unsigned char err;

        if (ide_devices[drive].Type == IDE_ATA) {
            err = ide_ata_access(ATA_READ, drive, lba, numsects, es, edi);
        } else if (ide_devices[drive].Type == IDE_ATAPI) {
            for (int i = 0; i < numsects; i++)
                err = ide_atapi_read(drive, lba + i, 1, es, edi + (i*2048));
        }

        package[0] = ide_printErr(drive, err);
    }
}

void ide_writeSectors(  unsigned char drive, 
                        unsigned char numsects, 
                        unsigned int lba,
                        unsigned short es, 
                        unsigned int edi) {
 
    if (drive > 3 || ide_devices[drive].Reserved == 0) {
        package[0] = 0x1;
    } else if (((lba + numsects) > ide_devices[drive].Size) && (ide_devices[drive].Type == IDE_ATA)) {
        package[0] = 0x2;
    } else {
        unsigned char err;

        if (ide_devices[drive].Type == IDE_ATA) {
            err = ide_ata_access(ATA_WRITE, drive, lba, numsects, es, edi);
        } else if (ide_devices[drive].Type == IDE_ATAPI) {
            err = 4;
        }

        package[0] = ide_printErr(drive, err);
    }
}

void ide_atapi_eject(unsigned char drive) {
    unsigned int   channel      = ide_devices[drive].Channel;
    unsigned int   slavebit      = ide_devices[drive].Drive;
    unsigned int   bus      = channels[channel].base;
    unsigned int   words      = 2048 / 2;               // Sector Size in Words.
    unsigned char  err = 0;
    ide_irq_invoked = 0;
    
    if (drive > 3 || ide_devices[drive].Reserved == 0)
        package[0] = 0x1;
    else if (ide_devices[drive].Type == IDE_ATA)
        package[0] = 20;
    else {
        ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = ide_irq_invoked = 0x0);
    
        atapi_packet[ 0] = /*ATAPI_CMD_EJECT*/ 0x1B;
        atapi_packet[ 1] = 0x00;
        atapi_packet[ 2] = 0x00;
        atapi_packet[ 3] = 0x00;
        atapi_packet[ 4] = 0x02;
        atapi_packet[ 5] = 0x00;
        atapi_packet[ 6] = 0x00;
        atapi_packet[ 7] = 0x00;
        atapi_packet[ 8] = 0x00;
        atapi_packet[ 9] = 0x00;
        atapi_packet[10] = 0x00;
        atapi_packet[11] = 0x00;
    
        ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);
    
        for(int i = 0; i < 4; i++) 
            ide_read(channel, ATA_REG_ALTSTATUS);

        ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);
        err = ide_polling(channel, 1);

        //else {
            asm("rep   outsw"::"c"(6), "d"(bus), "S"(atapi_packet));
            ide_wait_irq();

            err = ide_polling(channel, 1);

            if (err == 3)
                err = 0;
        //}

        package[0] = ide_printErr(drive, err);
    }
}