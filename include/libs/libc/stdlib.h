#ifndef _STDLIB_H_
#define _STDLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
    Converts an integer value to a null-terminated string using the
    specified base and stores the result in the array given by str 
    parameter.

    Online ref.: https://cplusplus.com/reference/cstdlib/itoa/
*/
char* itoa(int __value, char* __str, int __base);

/*
    Aborts the current process, producing an abnormal program 
    termination.

    Online ref.: https://cplusplus.com/reference/cstdlib/abort/
*/
__attribute__((__noreturn__)) void abort(void);

#ifdef __cplusplus
}
#endif

#endif