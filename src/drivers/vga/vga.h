#ifndef _VGA_H_
#define _VGA_H_

#include <stddef.h>
#include "kernel/kernel.h"


const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

// Video Graphics Array (VGA) driver
class Vga {
    private:
    static int _pallete;

    public:
    /*
    // VGA Colors for 1-bit modes
    enum color1x {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_WHITE = 1,
    };

    // VGA Colors for 2-bit modes
    enum color2x {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_CYAN = 1,
        VGA_COLOR_MAGENTA = 2,
        VGA_COLOR_GRAY = 3,
    };
    */

    // VGA Colors for 4-bit modes
    enum color4x {
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

    static void setPalete(int __bits);

    /*
    // Returns color entry for 1-bit pallete
    static u8 entryColor1x(enum Vga::color1x __foreground, enum Vga::color1x __background);

    // Returns color entry for 2-bit pallete
    static u8 entryColor2x(enum Vga::color2x __foreground, enum Vga::color2x __background);
    */

    // Returns color entry for default 4-bit pallete
    static u8 entryColor  (enum Vga::color4x __foreground, enum Vga::color4x __background);

    static u16 entry(uc __char, u8 __color);

    static void init();

};

#endif