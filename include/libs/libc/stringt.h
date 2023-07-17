#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

typedef const char* String;

int memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

size_t strlen(String str);

#endif