#ifndef _CB_ATA_ERRORS_H_
#define _CB_ATA_ERRORS_H_

#define ATA_ERROR_BAD_BLOCK             0x80    // Bad block
#define ATA_ERROR_UNCORRECTABLE         0x40    // Uncorrectable data
#define ATA_ERROR_MEDIA_CHANGE          0x20    // Media changed
#define ATA_ERROR_ID_MARK_NOT_FOUND     0x10    // ID mark not found
#define ATA_ERROR_MEDIA_CHANGE_REQUEST  0x08    // Media change request
#define ATA_ERROR_ABROT                 0x04    // Command aborted
#define ATA_ERROR_TRACK0_NOT_FOUND      0x02    // Track 0 not found
#define ATA_ERROR_NO_ADDRESS_MARK       0x01    // No address mark

#endif