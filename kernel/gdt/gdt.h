#ifndef _CB_GDT_H_
#define _CB_GDT_H_

#include <stdint.h>

typedef struct globalDescriptorTable_t {
    uint32_t limit;
    uint32_t base;
    uint8_t  access_byte;
    uint16_t flags;
} globalDescriptorTable_t;


extern void gdt_encodeEntry(uint8_t *target, struct globalDescriptorTable_t source);

#endif