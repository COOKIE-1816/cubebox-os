#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include <stddef.h>

typedef const char* String;

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

// Counts characters in __str string and returns count of them.
size_t strlen(String __str);

#ifdef __cplusplus
}
#endif

#endif
