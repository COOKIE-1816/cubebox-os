#ifndef _KERNEL_CURSOR_H_
#define _KERNEL_CURSOR_H_

#include <stdint.h>

namespace Kernel {
    // Cursor control for text mode. (VGA cursor)
    namespace Cursor {
        void cursor_enable();
        void cursor_disable();

        void cursor_update(int __x, int __y);
        uint16_t cursor_getPos();
    };
};

#endif