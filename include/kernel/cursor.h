#ifndef _KERNEL_CURSOR_H_
#define _KERNEL_CURSOR_H_

#include <stdint.h>

namespace Kernel {
    // Cursor control for text mode. (VGA cursor)
    namespace Cursor {
        extern void cursor_enable();
        extern void cursor_disable();

        extern void cursor_update(int __x, int __y);
        extern uint16_t cursor_getPos();
    };
};

#endif