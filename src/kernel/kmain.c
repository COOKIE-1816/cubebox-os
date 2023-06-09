#include <drivers/vga.h>
#include <kernel/tty.h>

void kmain(void);

void kmain(void) {
	tty_initialize();
	tty_writeString("CubeBox kernel 1.0.\n");
}
