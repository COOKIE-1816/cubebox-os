#ifndef _KERNEL_DEFS_TYPES_H_
#define _KERNEL_DEFS_TYPES_H_

#include <stdint.h>

/*
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
*/

#define i8		int8_t
#define i16		int16_t
#define i32		int32_t
#define i64		int64_t
#define u8		uint8_t
#define u16		uint16_t
#define u32		uint32_t
#define u64		uint64_t
#define f8		int_fast8_t
#define f16		int_fast16_t
#define f32		int_fast32_t
#define f64		int_fast64_t
#define fu8		uint_fast8_t
#define fu16	uint_fast16_t
#define fu32	uint_fast32_t
#define fu64	uint_fast64_t

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