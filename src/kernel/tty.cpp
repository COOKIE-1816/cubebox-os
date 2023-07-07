/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/tty.c
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Kernel module controlling TTY. - staticaly loaded.
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-39 UTC
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
    @@@@@@@@@@@@@&                          ,@@@@@@@                           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          File usage:                 
    @@@@@@@@@@@@@&                                          Contributors:               Vaclav Hajsman
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          Docs. reference:            
    @@@@@@@@@@@@@&                                          Online reference:           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          Copyright (C) Vaclav Hajsman (A.K.A. COOKIE) 2023. All rights reserved.
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          This file is licensed as a part of the project inself, and licensing information
    @@@@@@@@@@@@@&                                          Can be found in LICENSE file in root directory of this project.
============================================================================================================================================
*/

#include "kernel/tty.h"
#include "drivers/vga.h"
#include <stdint.h>
#include <stddef.h> 
//static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

using namespace VGA;

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
static uint16_t* tty_buffer;

const char* allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/*-+.\n,<>?:_\";'!\\|[]{}()` ";

int isAllowed(char c) {
	for(int i = 0; allowed[i]; i++) {
		if(allowed[i] == c)
			return 1;
	}

	return 0;
}

//static uint16_t* _img;
Kernel::TTY::tty_img tty_image() {
    Kernel::TTY::tty_img img;

    img.tty_row = tty_row;
    img.tty_column = tty_column;
    img.tty_color = tty_color;
    img.tty_buffer = tty_buffer;

    Kernel::TTY::writeString("TTY: Successfully created screen image.\n");
    return img;
}

void Kernel::TTY::tty_restore(tty_img __image) {
    tty_row = __image.tty_row;
    tty_column = __image.tty_column;
    tty_color = __image.tty_color;
    tty_buffer = __image.tty_buffer;
}
 
void Kernel::TTY::scroll(int rowsAmount) {
    for(int i = 0; i < rowsAmount; i++) {
        for (size_t row = 1; row < VGA_HEIGHT; ++row) {
            for (size_t col = 0; col < VGA_WIDTH; ++col) {
                const size_t index =    ( row      * VGA_WIDTH + col) * 2;
                const size_t newIndex = ((row - 1) * VGA_WIDTH + col) * 2;

                tty_buffer[newIndex]     = tty_buffer[index];
                tty_buffer[newIndex + 1] = tty_buffer[index + 1];
            }
        }

        const size_t lastRowOffset = (VGA_HEIGHT - 1) * VGA_WIDTH * 2;
        for (size_t col = 0; col < VGA_WIDTH; ++col) {
            const size_t index = lastRowOffset + col * 2;

            tty_buffer[index] = ' ';
            tty_buffer[index + 1] = tty_color;
        }

        --tty_row;
    }
}

void Kernel::TTY::breakLine() {
    tty_column = 0;

    if(tty_row == VGA_HEIGHT) {
        Kernel::TTY::scroll(1);
        return;
    }

    tty_row++;
}

void Kernel::TTY::tty_init(void) {
	tty_row = 0;
	tty_column = 0;

	tty_color = entryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = entry(' ', tty_color);
		}
	}
}
 
void Kernel::TTY::setColor(uint8_t color) {
	tty_color = color;
}
 
void Kernel::TTY::putEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = entry(c, color);
}
 
void Kernel::TTY::putChar(char c) {
	if(!isAllowed(c))
		c = '?';

    if(c == '\n') {
        Kernel::TTY::breakLine();
        return;
    }

	Kernel::TTY::putEntryAt(c, tty_color, tty_column, tty_row);

	if (tty_row == VGA_HEIGHT) {
        Kernel::TTY::scroll(1);
    }

	if (++tty_column == VGA_WIDTH) {
		Kernel::TTY::breakLine();

	}
	
}
 
void Kernel::TTY::write(String data, size_t size) {
	for (size_t i = 0; i < size; i++)
		Kernel::TTY::putChar(data[i]);
}
 
void Kernel::TTY::writeString(String data) {
	Kernel::TTY::write(data, strlen(data));
}

void tty_colored(uint8_t color, String data) {
    uint8_t prc = tty_color;

    Kernel::TTY::setColor(color);
    Kernel::TTY::writeString(data);

    Kernel::TTY::setColor(prc);
}

size_t Kernel::TTY::getRow() {
    return tty_row;
}