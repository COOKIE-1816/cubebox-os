#include "kernel/terminal.h"
#include "drivers/vga/vga.h"

inline void Terminal::init() {
    pos_x = 0;
    pos_y = 0;

    color = 0x07;
    buffer = (u16*) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			buffer[ y * VGA_WIDTH + x] = Vga::entry(' ', color);
		}
	}
}

inline void Terminal::setColor(u8 __color) {
    color = __color;
}

inline void Terminal::putEntry(char __c, u8 __color, size_t __pos_x, size_t __pos_y) {
	buffer[__pos_y * VGA_WIDTH + __pos_x] = Vga::entry(__c, __color);
}

inline void Terminal::putChar(char __c) {
    if(__c == '\n' || pos_x == VGA_WIDTH) {
        lineBreak();
        return;
    }

    if(pos_y == VGA_HEIGHT)
        scroll();

    putEntry(__c, color, pos_x, pos_y);

	/*if (++pos_x == VGA_WIDTH) {
		pos_x = 0;

		if (++pos_y == VGA_HEIGHT)
			pos_y = 0;
	}*/

    pos_x++;
}

inline void Terminal::write(const char* __data, size_t __size) {
    for(size_t i = 0; i < __size; i++) {
        putChar(__data[i]);
    }
}

inline void Terminal::wstring(String __data) {
    String __str = __data;

    write(__str, strlen(__str));
}



inline void Terminal::scroll() {
    for(size_t i = 0; i < VGA_WIDTH; i++) {
        buffer[i] = buffer[i + 1];
    }

    for(size_t i = 0; i < VGA_WIDTH; i++) {
        buffer[(VGA_HEIGHT - 1) * VGA_WIDTH] = Vga::entry(' ', color);
    }
}

inline void Terminal::lineBreak_noXChange() {
    if(pos_y != VGA_HEIGHT) {
        pos_y++;
        return;
    }

    scroll();
}

inline void Terminal::lineBreak() {
    lineBreak_noXChange();
    pos_x = 0;
}

/*inline void Terminal::wstyled(String __data_fmt) {
    u8 defaultColor = color;

    for(int i0 = 0; i0 < strlen(__data_fmt); i0++) {
        if((__data_fmt[i0] == '$' || __data_fmt[i0] == '%') && __data_fmt[i0 + 1] == 'r') {

        }
    }
}*/