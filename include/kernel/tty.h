#ifndef _CB_TTY_H_
#define _CB_TTY_H_

#include "libs/stringt.h"
#include <stdint.h>
#include <stddef.h>

namespace Kernel {
    namespace TTY {
        typedef struct tty_img {
            size_t tty_row;
            size_t tty_column;
            uint8_t tty_color;
            uint16_t* tty_buffer;
        } tty_img;

        tty_img tty_image();
        void tty_restore(tty_img __image);

        extern void tty_init(void);
        extern void setColor(uint8_t color);
        extern void putEntryAt(char c, uint8_t color, size_t x, size_t y);
        extern void putChar(char c);
        extern void write(String data, size_t size);
        extern void writeString(String data);
        extern void breakLine();
        extern void scroll(int rowsAmount);
        extern void colored(uint8_t color, String data);
        extern size_t getRow();
    };
};


//void printc(String data);

#endif