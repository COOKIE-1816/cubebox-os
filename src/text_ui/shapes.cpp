#include "kernel/tty.h"
#include "drivers/vga.h"
#include "text_ui/shapes.h"

using namespace VGA;
using namespace Kernel::TTY;

uint8_t _ec;

void drawLineH(size_t __start, size_t __end, size_t __y, enum vga_color __color) {
    _ec = entryColor(__color, __color);

    for(size_t i = __start; i < __start + __end - 2; i++) {
        putEntryAt('/', _ec, i, __y);
    }
}

void drawLineV(size_t __start, size_t __end, size_t __x, enum vga_color __color) {
    _ec = entryColor(__color, __color);

    for(size_t i = __start; i < __start + __end - 2; i++) {
        putEntryAt('/', _ec, __x, i);
    }
}

void drawRect(Rectangle __rect) {
    // This fixes a bug for some strange reason
    __rect.a --;
    __rect.b --;

    drawLineH(__rect.x, __rect.x + __rect.a, __rect.y,              __rect.borderColor);
    drawLineH(__rect.x, __rect.x + __rect.a, __rect.y + __rect.b,   __rect.borderColor);
    drawLineV(__rect.y, __rect.y + __rect.b, __rect.x,              __rect.borderColor);
    drawLineV(__rect.y, __rect.y + __rect.b, __rect.x + __rect.a,   __rect.borderColor);
}

