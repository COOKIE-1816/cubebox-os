#include "drivers/acpi.h"
#include "kernel/common.h"

// inline  dword *SMI_CMD = 0;
// inline  byte ACPI_ENABLE = 0;
// inline  byte ACPI_DISABLE = 0;
// inline  dword *PM1a_CNT = 0;
// inline  dword *PM1b_CNT = 0;
// inline word SLP_TYPa = 0;
// inline  word SLP_TYPb = 0;
// inline  word SLP_EN = 0;
// inline byte PM1_CNT_LEN = 0;
// inline word SCI_EN = 0;

// void _acpi_ensureEnabled() {

//     if(SCI_EN != 0)
//         acpi_enable();
// }

int acpi_shutdown(void) {
    _acpi_ensureEnabled();
        
    outb((unsigned int) PM1a_CNT, SLP_TYPa | SLP_EN );

    if ( PM1b_CNT != 0 )
        outb((unsigned int) PM1b_CNT, SLP_TYPb | SLP_EN );
    
    return 1;
}