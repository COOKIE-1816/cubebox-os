#pragma once

#ifndef _CB_TTY_H_
#define _CB_TTY_H_

#include <stddef.h>
#include <drivers/vga.h>

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_initialize();
void tty_setColor(uint8_t color);
void tty_putEntryAt(char c, uint8_t color, size_t x, size_t y);
void tty_putChar(char c);
void tty_write(const char* data, size_t size);
void tty_writeString(const char* data);
#endif