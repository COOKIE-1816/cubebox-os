#include "stdlib.h"
#include "stdio.h"

char* itoa(int __value, char* __str, int __base) {
    /*
        Converts an integer value to a null-terminated string using the
        specified base and stores the result in the array given by str 
        parameter.

        Online ref.: https://cplusplus.com/cstdlib/itoa/
    */

    char* rc;
    char* ptr;
    char* low;
    
    if ( __base < 2 || __base > 36 ) {
        *__str = '\0';

        return __str;
    }

    rc = ptr = __str;
    
    if ( __value < 0 && __base == 10 )
        *ptr++ = '-';
    
    low = ptr;
    
    do {
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + __value % __base];
        __value /= __base;
    } while ( __value );
    
    *ptr-- = '\0';
    
    while ( low < ptr ) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }


    return rc;
}

__attribute__((__noreturn__)) void abort(void) {
    #if defined(__is_libk)
        printf("kernel: panic: abort()\n");
        asm volatile("hlt");
    #else
        printf("abort()\n");
    #endif

	while (1) {} __builtin_unreachable();
}