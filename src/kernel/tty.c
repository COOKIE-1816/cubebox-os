#include <kernel/tty.h>
#include <lib/string.h>

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
	tty_putEntryAt(c, tty_color, tty_column, tty_row);

	if (++tty_column == VGA_WIDTH) {
		tty_column = 0;

		if (++tty_row == VGA_HEIGHT)
			tty_row = 0;
	}
}
 
void tty_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++){
        tty_putChar(data[i]);
    }
}
 
void tty_writeString(const char* data) {
	tty_write(data, strlen(data));
}