#ifndef _CB_TTY_H_
#define _CB_TTY_H_

#include "libs/stringt.h"
#include <stdint.h>
#include <stddef.h>

typedef struct tty_img {
    size_t tty_row;
    size_t tty_column;
    uint8_t tty_color;
    uint16_t* tty_buffer;
} tty_img;

tty_img tty_image();
void tty_restore(tty_img __image);

extern void tty_initialize(void);
extern void tty_setColor(uint8_t color);
extern void tty_putEntryAt(char c, uint8_t color, size_t x, size_t y);
extern void tty_putChar(char c);
extern void tty_write(String data, size_t size);
extern void tty_writeString(String data);
extern void tty_breakLine();
extern void tty_scroll(int rowsAmount);
extern void tty_colored(uint8_t color, String data);
extern size_t tty_getRow();
//void printc(String data);

#endif