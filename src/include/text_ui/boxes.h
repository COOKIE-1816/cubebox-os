#ifndef _CB_TEXTUI_BOXES_H_
#define _CB_TEXTUI_BOXES_H_

#include "kernel/tty.h"

typedef struct Box {
    size_t width;
    size_t height;

    size_t x;
    size_t y;

    uint8_t foreground;
    uint8_t background;

    bool hasTitle;
    String title;

    String body;

    bool dropShadow;
} Box;

void createBox(Box __box);
void createBox_keepBuffer(Box __box);
void restoreBuffer();
//void destroyBox();

#endif