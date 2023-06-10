#include "drivers/vga.h"

const size_t VGA_WIDTH  = 80;
const size_t VGA_HEIGHT = 25;
uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;


inline uint8_t vga_entryColor(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
inline uint16_t vga_entry(uc _uc, uint8_t color) {
	return (uint16_t) _uc | (uint16_t) color << 8;
}