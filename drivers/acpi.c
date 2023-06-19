#include "drivers/acpi.h"
#include "drivers/rtc.h"
#include "kernel/common.h"
#include "kernel/kdrivers.h"
#include "stringt.h"
#include <stdint.h>





struct RSDPtr {
    byte Signature[8];
    byte CheckSum;
    byte OemID[6];
    byte Revision;
    dword *RsdtAddress;
};

struct FACP {
    byte Signature[4];
    dword Length;
    byte unneded1[40 - 8];
    dword *DSDT;
    byte unneded2[48 - 44];
    dword *SMI_CMD;
    byte ACPI_ENABLE;
    byte ACPI_DISABLE;
    byte unneded3[64 - 54];
    dword *PM1a_CNT_BLK;
    dword *PM1b_CNT_BLK;
    byte unneded4[89 - 72];
    byte PM1_CNT_L
};

unsigned int *acpi_checkRSDPtr(unsigned int *ptr) {
   char *sig = "RSD PTR ";

   struct RSDPtr *rsdp = (struct RSDPtr *) ptr;

   byte *bptr;
   byte check = 0;
   int i;

   if (memcmp(sig, rsdp, 8) == 0) {
        bptr = (byte*) ptr;

        for (i=0; i<sizeof(struct RSDPtr); i++){
            check += *bptr;
            bptr++;
        }

        if (check == 0)
            return (unsigned int *) rsdp->RsdtAddress;
    }

    return NULL;
}

unsigned int *acpi_getRSDPtr(void) {
    unsigned int *addr;
    unsigned int *rsdp;

    for (addr = (unsigned int *) 0x000E0000; (int) addr<0x00100000; addr += 0x10/sizeof(addr)) {
        rsdp = acpi_checkRSDPtr(addr);

        if (rsdp != NULL)
            return rsdp;
    }

    int ebda = *((short *) 0x40E);
    ebda = ebda*0x10 &0x000FFFFF;

    for (addr = (unsigned int *) ebda; (int) addr<ebda+1024; addr+= 0x10/sizeof(addr)) {
        rsdp = acpi_checkRSDPtr(addr);

        if (rsdp != NULL)
            return rsdp;
    }

    return NULL;
}

int acpi_checkHeader(unsigned int *ptr, char *sig) {
    if (memcmp(ptr, sig, 4) == 0) {
        char check = 0;
        char *checkPtr = (char *) ptr;
        int len = *(ptr + 1);

        while (0<len--) {
            check += *checkPtr;
            checkPtr++;
        }

        if (check == 0)
            return 0;
    }

    return -1;
}

int acpi_enable(void) {
    if((inb((unsigned int) PM1a_CNT) &SCI_EN) == 0 ) {
        if (SMI_CMD != 0 && ACPI_ENABLE != 0) {
            outb((unsigned int) SMI_CMD, ACPI_ENABLE);
            
            int i;

            for (i=0; i<300; i++ ) {
                if((inb((unsigned int) PM1a_CNT) &SCI_EN) == 1)
                    break;

                rtc_sleep(1);
            }
            
            if (PM1b_CNT != 0) {
                for (; i<300; i++ ) {
                    if ( (inb((unsigned int) PM1b_CNT) &SCI_EN) == 1 )
                        break;

                    rtc_sleep(1);
                }
            }

            if (i<300) {
                tty_writeString("ACPI: Enabled.\n");
                return 0;
            } else {
                tty_writeString("ACPI: Err: could not enable ACPI.\n");
                return -1;
            }
        } else {
            tty_writeString("ACPI: Err: could not enable ACPI.\n");
            return -1;
        }
    } else {
        return 0;
    }
}

int acpi_init(void) {
    kdriver acpi;
    acpi.name = "ACPI";

    kdriver_statusMsg_create(acpi);

    unsigned int *ptr = acpi_getRSDPtr();

    if (ptr != NULL && acpi_checkHeader(ptr, "RSDT") == 0) {
        int entrys = *(ptr + 1);
        entrys = (entrys-36) /4;

        ptr += 36/4;

        while (0<entrys--) {
            if (acpi_checkHeader((unsigned int *) *ptr, "FACP") == 0) {
                entrys = -2;

                struct FACP *facp = (struct FACP *) *ptr;

                if (acpi_checkHeader((unsigned int *) facp->DSDT, "DSDT") == 0) {
                    char *S5Addr = (char *) facp->DSDT +36;
                    int dsdtLength = *(facp->DSDT+1) -36;

                    while (0 < dsdtLength--) {
                        if (memcmp(S5Addr, "_S5_", 4) == 0)
                            break;

                    S5Addr++;
                }

                if (dsdtLength > 0) {
                    if ( ( *(S5Addr-1) == 0x08 || ( *(S5Addr-2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 ) {
                        S5Addr += 5;
                        S5Addr += ((*S5Addr &0xC0)>>6) +2;

                        if (*S5Addr == 0x0A)
                            S5Addr++;

                        SLP_TYPa = *(S5Addr)<<10;
                        S5Addr++;

                        if (*S5Addr == 0x0A)
                            S5Addr++;

                        SLP_TYPb = *(S5Addr)<<10;

                        SMI_CMD = facp->SMI_CMD;

                        ACPI_ENABLE = facp->ACPI_ENABLE;
                        ACPI_DISABLE = facp->ACPI_DISABLE;

                        PM1a_CNT = facp->PM1a_CNT_BLK;
                        PM1b_CNT = facp->PM1b_CNT_BLK;
                        
                        PM1_CNT_LEN = facp->PM1_CNT_L;

                        SLP_EN = 1<<13;
                        SCI_EN = 1;

                        kdriver_statusMsg_status(KDRIVERS_OK);
                        return 0;
                    } else {
                        tty_writeString("ACPI: Err: _S5 parse error.\n");
                    }
                } else {
                    tty_writeString("ACPI: Err: _S5 not present.\n");
                }
            } else {
                tty_writeString("ACPI: Err: DSDT invalid.\n");
            }
         }

         ptr++;
      }

        tty_writeString("ACPI: Err: no valid FACP present.\n");
   } else {
        tty_writeString("ACPI: Err: error.\n");
   }

    kdriver_statusMsg_status(KDRIVERS_FAIL);
   return -1;
}
