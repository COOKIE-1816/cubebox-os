#ifndef _KERNEL_PANIC_H_
#define _KERNEL_PANIC_H_

/*
    Dumps memory contents to file, prints error message of last
    known error and halts the CPU.
*/
extern "C" void kpanic(String __error);

/*
    Calls kernel panic and passes last known error as __error 
    parameter automatically.

    ! Use in assembly.
*/
extern "C" void kcrash(void);

#endif