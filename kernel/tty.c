#include "kernel/tty.h"
#include "drivers/vga.h"
#include <stdint.h>
#include <stddef.h> 
//static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

char* allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/*-+.\n,<>?:_\";'!\\|[]{}()` ";

int isAllowed(char c) {
	for(int i = 0; allowed[i]; i++) {
		if(allowed[i] == c)
			return 1;
	}

	return 0;
}
 
void tty_scroll(int rowsAmount) {
    for(int _r = 0; _r < rowsAmount; _r++) {
        for(size_t _c = 0; _c < VGA_WIDTH; _c++)
            tty_buffer[_c - 1] = tty_buffer[_c];
    }
}

void tty_breakLine() {
    tty_column = 0;

    if(tty_row == VGA_HEIGHT) {
        tty_scroll(1);
        return;
    }

    tty_row++;
}

void tty_initialize(void) {
	tty_row = 0;
	tty_column = 0;

	tty_color = vga_entryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}
 
void tty_setColor(uint8_t color) {
	tty_color = color;
}
 
void tty_putEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = vga_entry(c, color);
}
 
void tty_putChar(char c) {
	if(!isAllowed(c))
		c = '?';

    if(c == '\n') {
        tty_breakLine();
        return;
    }

	tty_putEntryAt(c, tty_color, tty_column, tty_row);

	if (++tty_column == VGA_WIDTH) {
		tty_breakLine();

		/*if (++tty_row == VGA_HEIGHT)
			tty_scroll();*/
	}
}
 
void tty_write(String data, size_t size) {
	for (size_t i = 0; i < size; i++)
		tty_putChar(data[i]);
}
 
void tty_writeString(String data) {
	tty_write(data, strlen(data));
}

void tty_colored(uint8_t color, String data) {
    uint8_t prc = tty_color;

    tty_setColor(color);
    tty_writeString(data);

    tty_setColor(prc);
}