#include "drivers/floppy.h"
#include "kernel/common.h"
#include "kernel/tty.h"
#include "drivers/rtc.h"
#include "kernel/kdrivers.h"
#include "kernel/interrupt/irq.h"

#define floppy_dmalen 0x4800

unsigned _drives;

static const int floppy_base = 0x03f0;
static const int floppy_irq = 6;

static volatile int floppy_motor_ticks = 0;
static volatile int floppy_motor_state = 0;

static volatile uint8_t _floppyDiskIRQ = 0;

static String floppy_driveTypes[8] = {
    "none",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",
    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "unknown type",
    "unknown type"
};

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

    FLOPPY_DOR  = 2,  // digital output register
    FLOPPY_MSR  = 4,  // master status register, read only
    FLOPPY_FIFO = 5,  // data FIFO, in DMA operation for commands
    FLOPPY_CCR  = 7   // configuration control register, write only
};

enum floppy_commands {
    CMD_READ_TRACK      = 2,
    CMD_SPECIFY         = 3,
    CMD_SENSE_STATUS    = 4,
    CMD_WRITE_DATA      = 5,
    CMD_READ_DATA       = 6,
    CMD_RECALIBRATE     = 7,
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

enum { 
    floppy_motor_off = 0, 
    floppy_motor_on, 
    floppy_motor_wait 
};

typedef enum {
    floppy_dir_read = 1,
    floppy_dir_write = 2
} floppy_dir;


static const char floppy_dmabuf[floppy_dmalen]
                  __attribute__((aligned(0x8000)));

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

void _floppy_irq_wait() {
    while ( _floppyDiskIRQ == 0);
	_floppyDiskIRQ = 0;
}

inline void floppy_writeCmd(int base, char cmd) {
    for(int i = 0; i < 60; i++) {
        rtc_sleep(1);

        if(0x80 & inb(base + FLOPPY_MSR))
            return (void) outb(base + FLOPPY_FIFO, cmd);
    }

    tty_writeString("Floppy: err: writeCmd: timeout.");
}

inline unsigned char floppy_readData(int base) {
    for(int i = 0; i < 60; i++) {
        rtc_sleep(1);

        if(0x80 & inb(base + FLOPPY_MSR))
            return inb(base + FLOPPY_FIFO);
    }

    tty_writeString("Floppy: err: readData: timeout.");
    return 0;
}

void floppy_checkInterrupt(int __base, int* __st0, int* __cyl) {
    floppy_writeCmd(__base, CMD_SENSE_INTERRUPT);

    *__st0 = floppy_readData(__base);
    *__cyl = floppy_readData(__base);
}

int floppy_calibrate(int base) {
    int i, st0, cyl = -1;
    floppy_motor(base, floppy_motor_on);

    for(i = 0; i < 10; i++) {
        floppy_writeCmd(base, CMD_RECALIBRATE);
        floppy_writeCmd(base, 0);

        _floppy_irq_wait(floppy_irq);
        floppy_checkInterrupt(base, &st0, &cyl);
       
        if(st0 & 0xC0) {
            static String status[] = {
                0, 
                "error", 
                "invalid", 
                "drive" 
            };

            tty_writeString("floppy: calibrate: status: ");
            tty_writeString(status[st0 >> 6]);

            continue;
        }

        if(!cyl) { // found cylinder 0 ?
            floppy_motor(base, floppy_motor_off);
            return 0;
        }
    }

    tty_writeString("floppy_calibrate: 10 retries exhausted\n");
    floppy_motor(base, floppy_motor_off);

    return -1;
}


int floppy_reset(int base) {
    outb(base + FLOPPY_DOR, 0x00);
    outb(base + FLOPPY_DOR, 0x0C);

    _floppy_irq_wait(floppy_irq);

    {
        int st0, cyl;
        floppy_checkInterrupt(base, &st0, &cyl);
    }

    outb(base + FLOPPY_CCR, 0x00);

    //  - 1st byte is: bits[7:4] = steprate, bits[3:0] = head unload time
    //  - 2nd byte is: bits[7:1] = head load time, bit[0] = no-DMA
    //
    //  steprate    = (8.0ms - entry*0.5ms)*(1MB/s / xfer_rate)
    //  head_unload = 8ms * entry * (1MB/s / xfer_rate), where entry 0 -> 16
    //  head_load   = 1ms * entry * (1MB/s / xfer_rate), where entry 0 -> 128
    //

    floppy_writeCmd(base, CMD_SPECIFY);
    floppy_writeCmd(base, 0xdf);
    floppy_writeCmd(base, 0x02);

    if(floppy_calibrate(base))
        return -1;
}

void floppy_motor(int base, int onoff) {
    if(onoff) {
        if(!floppy_motor_state) {
            outb(base + FLOPPY_DOR, 0x1c);
            rtc_sleep(1);
        }

        floppy_motor_state = floppy_motor_on;
    } else {
        if(floppy_motor_state == floppy_motor_wait) {
            tty_writeString("floppy: motor: strange, fd motor-state already waiting.\n");
        }

        floppy_motor_ticks = 300;
        floppy_motor_state = floppy_motor_wait;
    }
}

void floppy_motor_kill(int base) {
    outb(base + FLOPPY_DOR, 0x0c);
    floppy_motor_state = floppy_motor_off;
}


//! THIS SHOULD BE STARTED IN A SEPARATE THREAD.
void floppy_timer() {
    while(1) {
        rtc_sleep(1);

        if(floppy_motor_state == floppy_motor_wait) {
            floppy_motor_ticks -= 50;

            if(floppy_motor_ticks <= 0)
                floppy_motor_kill(floppy_base);
        }
    }
}

int floppy_seek(int base, unsigned cyli, int head) {
    unsigned i, st0, cyl = -1;

    floppy_motor(base, floppy_motor_on);

    for(i = 0; i < 10; i++) {
        floppy_writeCmd(base, CMD_SEEK);
        floppy_writeCmd(base, head<<2);
        floppy_writeCmd(base, cyli);

        _floppy_irq_wait(floppy_irq);
        floppy_checkInterrupt(base, &st0, &cyl);

        if(st0 & 0xC0) {
            static String status[] = {
                "normal", 
                "error", 
                "invalid", 
                "drive"
            };

            tty_writeString("floppy: err: seek: status: \n");
            tty_writeString(status[st0 >> 6]);

            continue;
        }

        if(cyl == cyli) {
            floppy_motor(base, floppy_motor_off);
            return 0;
        }

    }

    tty_writeString("floppy_seek: 10 retries exhausted\n");

    floppy_motor(base, floppy_motor_off);
    return -1;
}

static void floppy_dma_init(floppy_dir dir) {
    union {
        unsigned char b[4];
        unsigned long l;
    } a, c;

    a.l = (unsigned) &floppy_dmabuf;
    c.l = (unsigned) floppy_dmalen - 1;

    if((a.l >> 24) || (c.l >> 16) || (((a.l&0xffff)+c.l)>>16))
        tty_writeString("floppy_dma_init: static buffer problem\n");

    unsigned char mode;

    switch(dir) {
        case floppy_dir_read:
            mode = 0x46;
            break;
        
        case floppy_dir_write:
            mode = 0x4a;
            break;

        default:
            tty_writeString("floppy_dma_init: invalid direction");
            return;
    }

    outb(0x0a, 0x06);

    outb(0x0c, 0xff);
    outb(0x04, a.b[0]);
    outb(0x04, a.b[1]);

    outb(0x81, a.b[2]);

    outb(0x0c, 0xff);
    outb(0x05, c.b[0]);
    outb(0x05, c.b[1]);

    outb(0x0b, mode);

    outb(0x0a, 0x02);
}

int floppy_doTrack(int base, unsigned cyl, floppy_dir dir) {
    unsigned char cmd;
    static const int flags = 0xC0;

    switch(dir) {
        case floppy_dir_read:
            cmd = CMD_READ_DATA | flags;
            break;

        case floppy_dir_write:
            cmd = CMD_WRITE_DATA | flags;
            break;

        default:
            tty_writeString("floppy_doTrack: invalid direction");
            return 0;
    }

    if(floppy_seek(base, cyl, 0)) 
        return -1;
    if(floppy_seek(base, cyl, 1))
        return -1;

    for(int i = 0; i < 20; i++) {
        floppy_motor(base, floppy_motor_on);
        floppy_dma_init(dir);

        rtc_sleep(1);

        floppy_writeCmd(base, cmd);
        floppy_writeCmd(base, 0);  
        floppy_writeCmd(base, cyl);
        floppy_writeCmd(base, 0);  
        floppy_writeCmd(base, 1);  
        floppy_writeCmd(base, 2);  
        floppy_writeCmd(base, 18); 
        floppy_writeCmd(base, 0x1b);
        floppy_writeCmd(base, 0xff);
       
        _floppy_irq_wait(floppy_irq);

        unsigned char   st0, 
                        st1, 
                        st2, 
                        rcy, 
                        rhe, 
                        rse, 
                        bps;

        st0 = floppy_readData(base);
        st1 = floppy_readData(base);
        st2 = floppy_readData(base);

        rcy = floppy_readData(base);
        rhe = floppy_readData(base);
        rse = floppy_readData(base);

        bps = floppy_readData(base);

        int error = 0;

        if(st0 & 0xC0) {
            static String status[] = {
                0, 
                "error", 
                "invalid command", 
                "drive not ready"
            };

            tty_writeString("floppy_doSector: status: ");
            tty_writeString(status[st0 >> 6]);

            error = 1;
        }

        if(st1 & 0x80) {
            tty_writeString("floppy_doSector: end of cylinder\n");
            error = 1;
        }

        if(st0 & 0x08) {
            tty_writeString("floppy_doSector: drive not ready\n");
            error = 1;
        }

        if(st1 & 0x20) {
            tty_writeString("floppy_doSector: CRC error\n");
            error = 1;
        }

        if(st1 & 0x10) {
            tty_writeString("floppy_doSector: controller timeout\n");
            error = 1;
        }

        if(st1 & 0x04) {
            tty_writeString("floppy_doSector: no data found\n");
            error = 1;
        }

        if((st1|st2) & 0x01) {
            tty_writeString("floppy_doSector: no address mark found\n");
            error = 1;
        }

        if(st2 & 0x40) {
            tty_writeString("floppy_doSector: deleted address mark\n");
            error = 1;
        }

        if(st2 & 0x20) {
            tty_writeString("floppy_doSector: CRC error in data\n");
            error = 1;
        }

        if(st2 & 0x10) {
            tty_writeString("floppy_doSector: wrong cylinder\n");
            error = 1;
        }

        if(st2 & 0x04) {
            tty_writeString("floppy_doSector: uPD765 sector not found\n");
            error = 1;
        }

        if(st2 & 0x02) {
            tty_writeString("floppy_doSector: bad cylinder\n");
            error = 1;
        }

        if(bps != 0x2) {
            tty_writeString("floppy_doSector: wanted 512B/sector, got ");
            tty_writeString((1<<(bps+7)));
            error = 1;
        }

        if(st1 & 0x02) {
            tty_writeString("floppy_doSector: not writable\n");
            error = 2;
        }

        if(!error) {
            floppy_motor(base, floppy_motor_off);
            return 0;
        }

        if(error > 1) {
            tty_writeString("floppy_doSector: not retrying..\n");
            floppy_motor(base, floppy_motor_off);

            return -2;
        }
    }

    floppy_motor(base, floppy_motor_off);
    return -1;
}

int floppy_readTrack(int base, unsigned cyl) {
    return floppy_doTrack(base, cyl, floppy_dir_read);
}

int floppy_writeTrack(int base, unsigned cyl) {
    return floppy_doTrack(base, cyl, floppy_dir_write);
}

void floppy_init() {
    kdriver floppy;
    floppy.name = "Floppy Disk Controller (FDC)";

    kdriver_statusMsg_create(floppy);

    floppy_detect(); 

    if(floppy_calibrate(floppy_base) != 0) {
        kdriver_statusMsg_status(KDRIVERS_FAIL);
        return;
    }

    kdriver_statusMsg_status(KDRIVERS_OK);
}