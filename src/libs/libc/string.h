#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include <stddef.h>

typedef const char* String;

#ifdef __cplusplus
extern "C" {
#endif


// Counts characters in __str string and returns count of them.
size_t strlen(String __str);

#ifdef __cplusplus
}
#endif

#endif
