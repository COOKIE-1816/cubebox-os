#include "kernel/cursor.h"
#include "kernel/common.h"
#include "drivers/vga.h"

uint8_t _cursor_start = 0;
uint8_t _cursor_end = 0;

void Kernel::Cursor::cursor_enable() {
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | _cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | _cursor_end);
}

void Kernel::Cursor::cursor_disable() {
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);  
}

void Kernel::Cursor::cursor_update(int __x, int __y) {
    uint16_t pos = __y * VGA_WIDTH + __x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t Kernel::Cursor::cursor_getPos() {
    uint16_t pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    return pos;
}