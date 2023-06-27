#ifndef _CB_TEXTUI_SHAPES_H_
#define _CB_TEXTUI_SHAPES_H_

#include <stddef.h>

typedef struct Rectangle {
    size_t a;   // Side A
    size_t b;   // Side B
    size_t x;   // Margin from left
    size_t y;   // Margin from top

    /*int fill;
    int fillColor;*/

    int borderColor;
} Rectangle;

void drawLineH(size_t __start, size_t __end, size_t __y, uint8_t __color);
void drawLineV(size_t __start, size_t __end, size_t __x, uint8_t __color);

void drawRect(Rectangle __rect);
void fillRect(Rectangle __rect, uint8_t __color);

#endif