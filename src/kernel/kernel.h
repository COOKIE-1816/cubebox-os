#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "kernel/defs/types.h"
#include "kernel/defs/macros.h"
#include "string.h"

/*
#define KVERSION_STRING (STRINGIFICATE(0.01.00.0a))
#define KDEVSTAGE_STRING (STRINGIFICATE(alpha))
*/

const String kernel_version =  (char*) "0.01.01.0a";
const String kernel_devStage = (char*) "alpha";



#endif
