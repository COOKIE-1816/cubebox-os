#include "drivers/acpi.h"
#include "kernel/common.h"
#include "kernel/error.h"
#include "kernel/tty.h"

using namespace ACPI;
using namespace Kernel;
using namespace Kernel::TTY;

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

int ACPI::acpi_shutdown(void) {
    if(get_SCI_EN() != 0)
        acpi_enable();
        
    outb((unsigned int) get_PM1a_CNT(), get_SLP_TYPa() | get_SLP_EN() );

    if ( get_PM1b_CNT() != 0 )
        outb((unsigned int) get_PM1b_CNT(), get_SLP_TYPb() | get_SLP_EN() );
    
    colored(10, "Failed to shutdown using ACPI. However, it should be now safe to power machine off manually.");
    error("ACPI_ERR_POWER_OFF_FAIL");
    return 1;
}