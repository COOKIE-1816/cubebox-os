#ifndef _CB_TEXTUI_SHAPES_H_
#define _CB_TEXTUI_SHAPES_H_

#include <stddef.h>

typedef struct Rectangle {
    size_t a;
    size_t b;
    size_t x;
    size_t y;

    /*int fill;
    int fillColor;*/

    int borderColor;
} Rectangle;

void drawRect(Rectangle __rect);
void fillRect(Rectangle __rect, uint8_t __color);

#endif