#pragma once
//#include "../kernel.h"
#include <stdint.h>

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_init(void);
void tty_clear(void);
void tty_setColor(uint8_t color);
void tty_putEntry(char c, uint8_t color, size_t x, size_t y);
void tty_putChar(char c);
void tty_write(const char* data, size_t size);
void print(const char* data);
void println(const char* data);