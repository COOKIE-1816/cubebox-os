#ifndef _KERNEL_TERMINAL_H_
#define _KERNEL_TERMINAL_H_

#include <stddef.h>
#include "kernel/kernel.h"
#include "libs/libc/string.h"

extern const size_t TAB_LENGTH;

// Terminal class used to print text to the screen.

size_t terminal_pos_x;
size_t terminal_pos_y;

u8 terminal_color;
u16* terminal_buffer;

void terminal_init();

// Clears the screen
void terminal_clear();

// Sets the color for next printing.
void terminal_setColor(u8 __color);

// Sets the color to default values.
void terminal_resetColor();

// Puts entry (char) with specified color to specified position.
void terminal_putEntry(char __c, u8 __color, size_t __pos_x, size_t __pos_y);

// Puts (prints) a new char to the display and buffer.
void terminal_putChar(char __c);

// Prints a specified char array of specified length.
void terminal_write(const char* __data, size_t __size);

// Prints a string
void terminal_wstring(String __data);

void terminal_tab();

/*
    Prints styled text

    Symbol $$ prints $
    Symbol %% prints %

    Symbol $0 set background black
    Symbol $1 set background blue
    Symbol $2 set background green
    Symbol $3 set background cyan
    Symbol $4 set background red
    Symbol $5 set background magenta
    Symbol $6 set background light grey

    Symbol %0 set foreground black
    Symbol %1 set foreground blue
    Symbol %2 set foreground green
    Symbol %3 set foreground cyan
    Symbol %4 set foreground red
    Symbol %5 set foreground magenta
    Symbol %6 set foreground brown
    Symbol %7 set foreground light grey
    Symbol %8 set foreground dark grey
    Symbol %9 set foreground light blue
    Symbol %b set foreground light green
    Symbol %c set foreground light cyan
    Symbol %d set foreground light red
    Symbol %e set foreground light magenta
    Symbol %f set foreground yellow
    Symbol %g set foreground white

    $r or %r will set defaults. 
    Styling automatically resets after printing.
*/
//static void wstyled(String __data_fmt);

//static void redrawBuffer();

// Makes a line break.
void terminal_lineBreak();

// Makes a line break, but does not reset position on x axis.
void terminal_lineBreak_noXChange();

// Scrolls.
void terminal_scroll();

    // A class to control text mode cursor.
size_t terminal_cursor_pos_x;
size_t terminal_cursor_pos_y;

void terminal_cursor_enable(u8 __start, u8 __end);
void terminal_cursor_disable();

// Move the cursor to the specified position.
void terminal_cursor_move(int __pos_x, int __pos_y);

// Get cursor position.
u16 terminal_cursor_getPos();

#endif
