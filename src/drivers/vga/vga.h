#ifndef _VGA_H_
#define _VGA_H_

#include <stddef.h>
#include "kernel/kernel.h"


extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;

    // VGA Colors for 4-bit modes
enum vga_color4x {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_setPalete(int __bits);

// Returns color entry for default 4-bit pallete
u8 vga_entryColor  (enum vga_color4x __foreground, enum vga_color4x __background);

u16 vga_entry(uc __char, u8 __color);
void vga_init();

#endif
