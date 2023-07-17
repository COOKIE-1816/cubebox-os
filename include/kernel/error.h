#ifndef _KERNEL_ERROR_H_
#define _KERNEL_ERROR_H_

namespace Kernel {
    // Gets last known error.
    char* getError();

    // Prints error message and informs kernel about error occured.
    void error(char* __error);
};

#endif