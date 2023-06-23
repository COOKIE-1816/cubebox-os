#ifndef _CB_ATA_STATUS_H_
#define _CB_ATA_STATUS_H_

#define ATA_SR_BUSY                 0x80    // Busy
#define ATA_SR_DRIVE_READY          0x40    // Drive ready
#define ATA_SR_DRIVE_WRITE_FAULT    0x20    // Drive write fault
#define ATA_SR_DRIVE_SEEK_COMPLETE  0x10    // Drive seek complete
#define ATA_SR_DRIVE_REQUEST_READY  0x08    // Data request ready
#define ATA_SR_CORRECT              0x04    // Corrected data
#define ATA_SR_INDEX                0x02    // Index
#define ATA_SR_ERROR                0x01    // Error

#endif