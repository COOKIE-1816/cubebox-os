#include "../tty/tty.h"
#include "../kernel.h"
#include "gdt.h"

void gdt_encode(uint8_t* target, struct GlobalDescriptorTable source) {
    if (source.limit > 0xFFFFF)
        println("GDT cannot encode limits larger than 0xFFFFF"); 
        // TODO: Create kerror module and implement it here instead of println

    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;

    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    target[5] = source.access_byte;
    target[6] |= (source.flags << 4)
}

void gdt_createDescriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor;

    descriptor = limit          & 0x000F0000;
    descriptor |= (flag << 8)   & 0x00F0FF00;
    descriptor |= (base >> 16)  & 0x000000FF;
    descriptor |= base          & 0xFF000000;

    descriptor <<= 32;

    descriptor |= base << 16;
    descriptor |= limit & 0x0000FFFF;

    // TODO: fix this piece of shit:
    //       printf("0x%.16llX\n", descriptor);
}

void gdt_init(void) {
    gdt_createDescriptor(0, 0, 0);
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    kernel_outputModuleLoadMessage(0, "Load '", "'", "Global Descriptor Table (GDT)");
}