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

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

char* allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/*-+.\n,<>?:_\";'!\\|[]{}()` ";

int isAllowed(char c) {
	for(int i = 0; allowed[i]; i++) {
		if(allowed[i] == c)
			return 1;
	}

	return 0;
}
 
void tty_scroll(int rowsAmount) {
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

void tty_breakLine() {
    tty_column = 0;

    if(tty_row == VGA_HEIGHT) {
        tty_scroll(1);
        return;
    }

    tty_row++;
}

void tty_initialize(void) {
	tty_row = 0;
	tty_column = 0;

	tty_color = vga_entryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}
 
void tty_setColor(uint8_t color) {
	tty_color = color;
}
 
void tty_putEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = vga_entry(c, color);
}
 
void tty_putChar(char c) {
	if(!isAllowed(c))
		c = '?';

    if(c == '\n') {
        tty_breakLine();
        return;
    }

	tty_putEntryAt(c, tty_color, tty_column, tty_row);

	if (tty_row == VGA_HEIGHT) {
        tty_scroll(1);
    }

	if (++tty_column == VGA_WIDTH) {
		tty_breakLine();

	}
	
}
 
void tty_write(String data, size_t size) {
	for (size_t i = 0; i < size; i++)
		tty_putChar(data[i]);
}
 
void tty_writeString(String data) {
	tty_write(data, strlen(data));
}

void tty_colored(uint8_t color, String data) {
    uint8_t prc = tty_color;

    tty_setColor(color);
    tty_writeString(data);

    tty_setColor(prc);
}