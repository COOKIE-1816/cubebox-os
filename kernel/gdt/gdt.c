#include "kernel/gdt/gdt.h"
#include "kernel/tty.h"
#include <stdint.h>
//#include <cstdint>

void printAddress(const void* ptr) {
    uintptr_t address = (uintptr_t)ptr;

    int numDigits = sizeof(address) * 2;
    char hexDigits[] = "0123456789ABCDEF";

    for (int i = numDigits - 1; i >= 0; i--) {
        uint8_t nibble = (address >> (i * 4)) & 0xF;

        tty_writeString(hexDigits[nibble]);
    }
}

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

void init_gdt() {
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;

   gdt_setGate(0, 0, 0, 0, 0);
   gdt_setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
   gdt_setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
   gdt_setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
   gdt_setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

   gdt_flush((uint32_t) &gdt_ptr); // * NOTE: Defined in gdt.asm
}

void gdt_setGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

void gdt_createDescriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor;
 
    descriptor  =  limit       & 0x000F0000;
    descriptor |= (flag <<  8) & 0x00F0FF00;
    descriptor |= (base >> 16) & 0x000000FF;
    descriptor |=  base        & 0xFF000000;
 
    descriptor <<= 32;
 
    descriptor |= base  << 16;
    descriptor |= limit  & 0x0000FFFF;

    /*int v =  42;
    printAddress(&v);*/
 
    //printf("0x%.16llX\n", descriptor);
    /*tty_writeString("Descriptor: ");
    printAddress(&descriptor);
    tty_writeString("\n");*/
}