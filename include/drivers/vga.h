/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/vga.h
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C (header)
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Headers for CubeBox VGA driver
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-43 UTC
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

#ifndef _CB_VGA_H
#define _CB_VGA_H

#include <stdint.h>
#include <stddef.h>
#include "kernel/kdrivers.h"

typedef unsigned char uc;

extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;
extern uint16_t* const VGA_MEMORY;

namespace VGA {
    enum vga_color {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15,
    };

    extern uint8_t vga_entryColor(enum vga_color fg, enum vga_color bg);
    extern uint16_t vga_entry(uc _uc, uint8_t color);
}







//kdriver systemDrv_vga;

#endif