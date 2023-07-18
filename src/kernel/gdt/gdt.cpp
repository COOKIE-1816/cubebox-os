#include "kernel/gdt.h"
#include "kernel/tty.h"
#include "kernel/panic.h"

using namespace Kernel::TTY;

typedef struct _GDT {
    uint32_t  base;
    uint32_t  limit;
    uint32_t  access;
    uint16_t  flags;
} _GDT;

void gdt_encodeEntry(uint8_t *__target, _GDT __source) {
    if(__source.limit > 0xFFFFF) {
        kpanic("GDT_ERR_LIMIT_LARGE\n");
        return;
    }

    __target[0] = __source.limit &          0xFF;
    __target[1] = (__source.limit >> 8) &   0xFF;
    __target[6] = (__source.limit >> 16) &  0xFF;

    __target[2] = __source.base & 0xFF;
    __target[3] = (__source.base >> 8) & 0xFF;
    __target[4] = (__source.base >> 16) & 0xFF;
    __target[7] = (__source.base >> 24) & 0xFF;

    __target[5] = __source.access;

    __target[6] |= (__source.flags << 4);
}

extern void setGdt(void);
extern void reloadSegments(void);

void Kernel::GDT::gdt_init() {
    asm("cli"); // Disable interrupts
}

void Kernel::GDT::createDescriptor(uint32_t __base, uint32_t __limit, uint16_t __flag) {
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  __limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (__flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (__base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  __base        & 0xFF000000;         // set base bits 31:24
 
    descriptor <<= 32;
 
    descriptor |= __base  << 16;                       // set base bits 15:0
    descriptor |= __limit  & 0x0000FFFF;               // set limit bits 15:0
 
    //printf("0x%.16llX\n", descriptor);
}

void Kernel::GDT::gdt_install() {
    createDescriptor(0, 0, 0);
    createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3));
}