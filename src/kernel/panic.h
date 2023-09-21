#ifndef _PANIC_H_
#define _PANIC_H_

#include "string.h"
#include "kernel/kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

/*  Kernel panic function.

    Prints error code on TTY, disables
    interrupts and halts the CPU.          */
void panic(string __error);

#ifdef __cplusplus
}
#endif

#endif
