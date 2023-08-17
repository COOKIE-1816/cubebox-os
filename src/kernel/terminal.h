#ifndef _KERNEL_TERMINAL_H_
#define _KERNEL_TERMINAL_H_

#include <stddef.h>
#include "kernel/kernel.h"
#include "libs/libc/string.h"

// Terminal class used to print text to the screen.
class Terminal {
    private:
    static size_t pos_x;
    static size_t pos_y;

    static u8 color;
    static u16* buffer;

    public:
    static void init();
    
    // Clears the screen
    static void clear();

    // Sets the color for next printing.
    static void setColor(u8 __color);
    
    // Sets the color to default values.
    static void resetColor();

    // Puts entry (char) with specified color to specified position.
    static void putEntry(char __c, u8 __color, size_t __pos_x, size_t __pos_y);

    // Puts (prints) a new char to the display and buffer.
    static void putChar(char __c);

    // Prints a specified char array of specified length.
    static void write(const char* __data, size_t __size);

    // Prints a string
    static void wstring(String __data);

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
    static void lineBreak();

    // Makes a line break, but does not reset position on x axis.
    static void lineBreak_noXChange();

    // Scrolls.
    static void scroll();

    // A class to control text mode cursor.
    class Cursor {
        private:
        static size_t pos_x;
        static size_t pos_y;

        public:
        static void enable(u8 __start, u8 __end);
        static void disable();

        // Move the cursor to the specified position.
        static void move(int __pos_x, int __pos_y);

        // Get cursor position.
        static u16 getPos();
    };
};

#endif