#include <stdint.h>
#include <stdlib.h>
#include "kernel/stack.h"

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn)) void stack_chk_fail(void) {
    #if __STDC_HOSTED__
        abort();
    #elif __is_cb_kernel
        panic("KERNEL_ERR_STACK_SMASH");
    #endif
}