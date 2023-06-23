#include "kernel/tty.h"
#include "drivers/vga.h"
#include "text_ui/shapes.h"

uint8_t _ec;

void _drawVert(Rectangle __rect) {
    _ec = vga_entryColor(__rect.borderColor, __rect.borderColor);

    for(size_t i = 0; i < __rect.b) {
        tty_putEntryAt(' ', _ec, __rect.x + i, __rect.y);
    }

    for(size_t i = 0; i < __rect.b) {
        tty_putEntryAt(' ', _ec, __rect.x + i, __rect.y + __rect.a);
    }
}

void drawRect(Rectangle __rect) {
    _drawVert(__rect);
}