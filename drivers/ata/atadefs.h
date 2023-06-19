#ifndef _CB_ATA_DEFS_H_
#define _CB_ATA_DEFS_H_

#include "drivers/ata/defs/atacmd.h"
//#include "drivers/ata/defs/atadefs.h"
#include "drivers/ata/defs/ataerr.h"
#include "drivers/ata/defs/atareg.h"
#include "drivers/ata/defs/atastatus.h"

#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01

#define ATA_PRIMARY    0x00
#define ATA_SECONDARY  0x01

#define ATA_READ       0x00
#define ATA_WRITE      0x01

#endif