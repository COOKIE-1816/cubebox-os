#ifndef _KERNEL_DEFS_TYPES_H_
#define _KERNEL_DEFS_TYPES_H_

#include <stdint.h>

/*
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
*/

#define uc unsigned char
#define cc const char*

/*
typedef unsigned char uc;
typedef const char* cc;
*/

typedef struct name_struct {
    cc shortName;
    cc name;
    int numId;
} name_t;

typedef u32 address_t;

#endif