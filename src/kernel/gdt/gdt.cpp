#include "kernel/gdt.h"
#include <stdio.h>

u64 Gdt::createDescriptor(gdt_descriptor_template_t __descriptor) {
    u64 descriptor;
 
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    descriptor <<= 32;
 
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
 
    printf("0x%.16llX\n", descriptor);
}

void Gdt::encodeEntry(u8* __target, gdt_descriptor_template_t __source) {
    if (__source.limit > 0xFFFFF) {
        printf("Gdt: error: GDT entry too large (> 0x000fffff).");
        return;
    }
 
    __target[0] = __source.limit & 0xFF;
    __target[1] = (__source.limit >> 8) & 0xFF;
    __target[6] = (__source.limit >> 16) & 0x0F;
 
    __target[2] = __source.base & 0xFF;
    __target[3] = (__source.base >> 8) & 0xFF;
    __target[4] = (__source.base >> 16) & 0xFF;
    __target[7] = (__source.base >> 24) & 0xFF;
 
    __target[5] = __source.access_byte;
 
    __target[6] |= (__source.flags << 4);
}

