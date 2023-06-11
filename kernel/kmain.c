#include "kernel/tty.h"
#include "drivers/vga.h"
#include "kernel/gdt/gdt.h"
#include "kernel/gdt/gdtdef.h"

String unstableWarning = "WARNING: UNSTABLE RELEASE, USE AT YOUR OWN RISK!\n";

void drawLine() {
    for(size_t i = 0; i < VGA_WIDTH; i++)
        tty_writeString("-");
}

void kernel_initializeKernelParticipals() {
    tty_initialize();
}

void kernel_main(void) {
    kernel_initializeKernelParticipals();

    tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n");
    tty_writeString("Copyright (C) Vaclav Hajsman 2023\n");
    drawLine();

    tty_colored(14, unstableWarning);

    gdt_createDescriptor(0, 0x00000000, 0x000000      );
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3));
}