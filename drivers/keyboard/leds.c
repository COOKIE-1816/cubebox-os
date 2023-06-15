/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/keyboard/leds.c
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Driver for keyboard LED indicators.
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-15 UTC
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

#include "kernel/common.h"
#include "drivers/keyboard/leds.h"
#include "drivers/keyboard.h"
#include "drivers/rtc.h"

inline void keyboard_leds_set(bool n, bool c, bool s) {
    uint8_t data = 0;

	data = (s) ? (data  | 1) : (data & 1);
	data = (n) ? (n     | 2) : (n    & 2);
	data = (c) ? (n     | 4) : (n    & 4);
 
	keyboard_enc_sendCmd(keyboard_ENC_CMD_SET_LED);
	keyboard_enc_sendCmd(data);
}

inline void keyboard_leds_blink() {
    bool state = false;

    while(true) {
        keyboard_leds_set(false, state, false);
        state = !state;

        rtc_sleep(1);
    }
}