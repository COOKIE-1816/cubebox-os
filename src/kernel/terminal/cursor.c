#include "kernel/terminal.h"
#include "kernel/common/io.h"
#include "drivers/vga/vga.h"

void terminal_cursor_enable(u8 __start, u8 __end) {
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | __start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | __end);
}

void terminal_cursor_disable() {
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void terminal_cursor_move(int __pos_x, int __pos_y) {
    uint16_t pos = __pos_y * VGA_WIDTH + __pos_x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (u8) (pos & 0xFF));

	outb(0x3D4, 0x0E);
	outb(0x3D5, (u8) ((pos >> 8) & 0xFF));
}

u16 terminal_cursor_getPos() {
    u16 pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((u16) inb(0x3D5)) << 8;

    return pos;
}
