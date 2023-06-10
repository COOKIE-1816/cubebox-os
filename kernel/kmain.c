#include "kernel/tty.h"

String unstableWarning = "WARNING: UNSTABLE RELEASE, USE AT YOUR OWN RISK!\n";

void kernel_initializeKernelParticipals() {
    tty_initialize();
}

void kernel_main(void) {
    kernel_initializeKernelParticipals();

    tty_writeString("CubeBox, kernel v0.0.1.0a - Alpha phase.\n");

    for(int s = 0; s < 30; s++)
        tty_writeString("Copyright (C) Vaclav Hajsman 2023\n\n");
    
    tty_writeString(unstableWarning);
}