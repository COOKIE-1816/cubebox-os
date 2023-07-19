#ifndef _KERNEL_DEFS_VECTORS_H_
#define _KERNEL_DEFS_VECTORS_H_

#include "kernel/defs/macros.h"

#define INTR_PIT 0x00
#define INTR_KBD 0x01
#define INTR_CSD 0x02 // casscade
#define INTR_COM2 0x03
#define INTR_COM1 0x04
#define INTR_LPT2 0x05
#define INTR_FLP 0x06
#define INTR_SPU 0x07 // spurious interrupt
#define INTR_LPT1 0x07
#define INTR_RTC 0x08
#define INTR_LGC 0x09 // legacy SCSI
#define INTR_SCSI 0x0A
#define INTR_SCSI 0x0B
#define INTR_MSE 0x0C // PS2 mouse
#define INTR_FPU 0x0D
#define INTR_CPR 0x0D // Coprocessor
#define INTR_IPR 0x0D // Inter-processor
#define INTR_ATA1 0x0E // Primary ATA harddisk
#define INTR_ATA2 0x0F // Secondary ATA harddisk

#define VECT_EXC_0 0x00
#define VECT_EXC_1 0x1F
#define VECT_I07_0 0x08
#define VECT_I07_1 0x0E
#define VECT_I8E_0 70h
#define VECT_I8E_1 78h

#define PORT_CPIC0 20h
#define PORT_MPIC0 21h
#define PORT_KBDDA 60h
#define PORT_KBDCM 64h

#endif