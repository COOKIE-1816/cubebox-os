#include "tty.h"
#include "../../drivers/vga/vga.h"
#include "../kernel.h"
//#include <stdint.h>

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_init(void) {
	tty_color = vga_entryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = (uint16_t*) 0xB8000;

	tty_clear();
}

void tty_clear(void) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}

	tty_row = 0; tty_column = 0;
}

void tty_setColor(uint8_t color) {
	tty_color = color;
}

void tty_putEntry(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = vga_entry(c, color);
}

void tty_putChar(char c) {
	tty_putEntry(c, tty_color, tty_column, tty_row);

	if (++tty_column == VGA_WIDTH) {
		tty_column = 0;
		if (++tty_row == VGA_HEIGHT) tty_row = 0;
	}
}

void tty_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++) tty_putChar(data[i]);
}

void print(const char* data) {
	tty_write(data, strlen(data));
}

void println(const char* data) {
	tty_write("\n", 1);
	tty_write(data, strlen(data));
}