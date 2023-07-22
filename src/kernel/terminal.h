#ifndef _KERNEL_TERMINAL_H_
#define _KERNEL_TERMINAL_H_

#include <stddef.h>
#include "kernel/kernel.h"
#include "libs/libc/string.h"

class Terminal {
    private:
    static size_t pos_x;
    static size_t pos_y;

    static u8 color;
    static u16* buffer;

    public:
    static void init();

    static void setColor(u8 __color);
    static void putEntry(char __c, u8 __color, size_t __pos_x, size_t __pos_y);
    static void putChar(char __c);

    static void write(const char* __data, size_t __size);
    static void wstring(String __data);

    static void lineBreak();
    static void lineBreak_noXChange();

    static void scroll();

    class Cursor {
        private:
        static size_t pos_x;
        static size_t pos_y;

        public:
        static void enable();
        static void disable();

        static void move(size_t __pos_x, size_t __pos_y);
        static size_t getPos();
    };
};

#endif