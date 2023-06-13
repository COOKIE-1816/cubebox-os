/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/vga.c
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 CubeBox VGA drivers
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-42 UTC
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
    @@@@@@@@@@@@@&                          ,@@@@@@@                           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          File usage:                 
    @@@@@@@@@@@@@&                                          Contributors:               
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

#include "drivers/vga.h"

const size_t VGA_WIDTH  = 80;
const size_t VGA_HEIGHT = 25;
uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;


inline uint8_t vga_entryColor(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
inline uint16_t vga_entry(uc _uc, uint8_t color) {
	return (uint16_t) _uc | (uint16_t) color << 8;
}