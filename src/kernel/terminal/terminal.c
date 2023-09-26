#include "kernel/terminal.h"
#include "drivers/vga/vga.h"

u8 color_default = 0x07;

void terminal_resetColor() {
    terminal_color = color_default;
}

void terminal_clear() {
    terminal_pos_x = 0;
    terminal_pos_y = 0;

    terminal_buffer = (u16*) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_init() {
    terminal_resetColor();
    terminal_clear();
}

void terminal_setColor(u8 __color) {
    terminal_color = __color;
}

void terminal_putEntry(char __c, u8 __color, size_t __pos_x, size_t __pos_y) {
	terminal_buffer[__pos_y * VGA_WIDTH + __pos_x] = vga_entry(__c, __color);
}



void terminal_tab() {
	if(TAB_LENGTH < VGA_WIDTH - terminal_pos_x) {
		terminal_lineBreak();
		return;
	}

    //const size_t m = VGA_WIDTH / TAB_LENGTH;

	//const size_t indent[/*(int) m*/ 85 / 8];
	//size_t indentchar;

/*
	for(size_t i = 0; i < VGA_WIDTH / TAB_LENGTH; i++) {
		indent[i] = i * TAB_LENGTH;
			
		if(indent[i] > terminal_pos_x) {
			indentchar = indent[i];
			break;
		}
	}
		
	terminal_pos_x = indentchar;

*/		

}

void terminal_putChar(char __c) {
	if(__c == '\t') {
		terminal_tab();
		return;
	}
	
    if(__c == '\n' || terminal_pos_x == VGA_WIDTH) {
        terminal_lineBreak();
        return;
    }

    if(terminal_pos_y == VGA_HEIGHT)
        terminal_scroll();

    terminal_putEntry(__c, terminal_color, terminal_pos_x, terminal_pos_y);

	/*if (++pos_x == VGA_WIDTH) {
		pos_x = 0;

		if (++pos_y == VGA_HEIGHT)
			pos_y = 0;
	}*/

    terminal_pos_x++;
}

void terminal_write(const char* __data, size_t __size) {
    for(size_t i = 0; i < __size; i++) {
        terminal_putChar(__data[i]);
    }
}

void terminal_wstring(String __data) {
    String __str = __data;

    terminal_write(__str, strlen(__str));
}



void terminal_scroll() {
    for(size_t i = 0; i < VGA_WIDTH; i++) {
        terminal_buffer[i] = terminal_buffer[i + 1];
    }

    for(size_t i = 0; i < VGA_WIDTH; i++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH] = vga_entry(' ', terminal_color);
    }
}

void terminal_lineBreak_noXChange() {
    if(terminal_pos_y != VGA_HEIGHT) {
        terminal_pos_y++;
        return;
    }

    terminal_scroll();
}

void terminal_lineBreak() {
    terminal_lineBreak_noXChange();
    terminal_pos_x = 0;
}

/*inline void terminal_wstyled(String __data_fmt) {
    u8 defaultColor = color;

    for(int i0 = 0; i0 < strlen(__data_fmt); i0++) {
        if((__data_fmt[i0] == '$' || __data_fmt[i0] == '%') && __data_fmt[i0 + 1] == 'r') {

        }
    }
}*/
