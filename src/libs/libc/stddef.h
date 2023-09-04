#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <stdint.h>

typedef long size_t;

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*) 0) -> MEMBER)
#define sizeof()

#endif