#ifndef _CB_ATA_CMD_H_
#define _CB_ATA_CMD_H_

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

/*
#define      ATAPI_CMD_READ       0xA8
#define      ATAPI_CMD_EJECT      0x1B
*/

#define ATA_IDENTIFY_DEVICETYPE   0
#define ATA_IDENTIFY_CYLINDERS    2
#define ATA_IDENTIFY_HEADS        6
#define ATA_IDENTIFY_SECTORS      12
#define ATA_IDENTIFY_SERIAL       20
#define ATA_IDENTIFY_MODEL        54
#define ATA_IDENTIFY_CAPABILITIES 98
#define ATA_IDENTIFY_FIELDVALID   106
#define ATA_IDENTIFY_MAX_LBA      120
#define ATA_IDENTIFY_COMMANDSETS  164
#define ATA_IDENTIFY_MAX_LBA_EXT  200

#endif