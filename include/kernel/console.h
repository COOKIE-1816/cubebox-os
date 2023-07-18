#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "stringt.h"

namespace Kernel {
    // CLI interface
    namespace Console {
        // Force console to leave automatically when any error occurs.
        //bool strictMode;

        /*
            Stores all command syntaxes executed in console. Can
            be cycled using arrows (up and down).

            Maximum is 80.
            0 for disable.
        */
        int commandBuffer;

        void enter();

        /*
            Force console to leave as soon as possible. Also 
            triggered using EXIT command or F2 key.
        */
        void leave();

        /*
            Sets hint for console. The hint is printed out after
            the prefix and is grayed out. Automatically hides when
            user starts typing.

            __hint can be up to 80 characters long.
        */
        void setHint(bool __enable, String __hint);
    };
};

#endif