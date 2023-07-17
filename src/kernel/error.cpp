#include "kernel/error.h"
#include "kernel/tty.h"

using namespace Kernel::TTY;

inline char* lastKnownError;

char* Kernel::getError() {
    return lastKnownError;
}

void Kernel::error(char* __error) {
    lastKnownError = __error;

    colored(4, "ERROR ");
    writeString((String) __error);
    writeString("\n");
}