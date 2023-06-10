#include "kernel/tty.h"
#include "drivers/vga.h"

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

    //tty_writeString(unstableWarning);
    tty_colored(6, unstableWarning);
}