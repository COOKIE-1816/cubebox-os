/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/keyboard.h
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C (header)
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Header file for keyboard driver.
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-18 UTC
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

#ifndef _CB_KEYBOARD_H_
#define _CB_KEYBOARD_H_

#include <stdint.h>
#include "cboolean.h"

#include "drivers/keyboard/kbderr.h"
#include "drivers/keyboard/leds.h"
#include "drivers/keyboard/scancodes.h"
#include "drivers/keyboard/keycode.h"

enum keyboard_ENCODER_IO {
	keyboard_ENC_INPUT_BUF	=	0x60,
	keyboard_ENC_CMD_REG	=	0x60
};
 
enum keyboard_CTRL_IO {
	keyboard_CTRL_STATS_REG	=	0x64,
	keyboard_CTRL_CMD_REG	=	0x64
};

enum keyboard_CTRL_STATS_MASK {
	keyboard_CTRL_STATS_MASK_OUT_BUF	=	1,  		//00000001
	keyboard_CTRL_STATS_MASK_IN_BUF	    =	2,  		//00000010
	keyboard_CTRL_STATS_MASK_SYSTEM	    =	4,  		//00000100
	keyboard_CTRL_STATS_MASK_CMD_DATA	=	8,  		//00001000
	keyboard_CTRL_STATS_MASK_LOCKED	    =	0x10,		//00010000
	keyboard_CTRL_STATS_MASK_AUX_BUF	=	0x20,		//00100000
	keyboard_CTRL_STATS_MASK_TIMEOUT	=	0x40,		//01000000
	keyboard_CTRL_STATS_MASK_PARITY	    =	0x80		//10000000
};

enum keyboard_ENC_CMDS {
	keyboard_ENC_CMD_SET_LED				=	0xED,
	keyboard_ENC_CMD_ECHO					=	0xEE,
	keyboard_ENC_CMD_SCAN_CODE_SET			=	0xF0,
	keyboard_ENC_CMD_ID					    =	0xF2,
	keyboard_ENC_CMD_AUTODELAY				=	0xF3,
	keyboard_ENC_CMD_ENABLE				    =	0xF4,
	keyboard_ENC_CMD_RESETWAIT				=	0xF5,
	keyboard_ENC_CMD_RESETSCAN				=	0xF6,
	keyboard_ENC_CMD_ALL_AUTO				=	0xF7,
	keyboard_ENC_CMD_ALL_MAKEBREAK			=	0xF8,
	keyboard_ENC_CMD_ALL_MAKEONLY			=	0xF9,
	keyboard_ENC_CMD_ALL_MAKEBREAK_AUTO	    =	0xFA,
	keyboard_ENC_CMD_SINGLE_AUTOREPEAT		=	0xFB,
	keyboard_ENC_CMD_SINGLE_MAKEBREAK		=	0xFC,
	keyboard_ENC_CMD_SINGLE_BREAKONLY		=	0xFD,
	keyboard_ENC_CMD_RESEND				    =	0xFE,
	keyboard_ENC_CMD_RESET					=	0xFF
};

enum keyboard_CTRL_CMDS {
	keyboard_CTRL_CMD_READ				=	0x20,
	keyboard_CTRL_CMD_WRITE				=	0x60,
	keyboard_CTRL_CMD_SELF_TEST			=	0xAA,
	keyboard_CTRL_CMD_INTERFACE_TEST	=	0xAB,
	keyboard_CTRL_CMD_DISABLE			=	0xAD,
	keyboard_CTRL_CMD_ENABLE			=	0xAE,
	keyboard_CTRL_CMD_READ_IN_PORT		=	0xC0,
	keyboard_CTRL_CMD_READ_OUT_PORT		=	0xD0,
	keyboard_CTRL_CMD_WRITE_OUT_PORT	=	0xD1,
	keyboard_CTRL_CMD_READ_TEST_INPUTS	=	0xE0,
	keyboard_CTRL_CMD_SYSTEM_RESET		=	0xFE,
	keyboard_CTRL_CMD_MOUSE_DISABLE		=	0xA7,
	keyboard_CTRL_CMD_MOUSE_ENABLE		=	0xA8,
	keyboard_CTRL_CMD_MOUSE_PORT_TEST	=	0xA9,
	keyboard_CTRL_CMD_MOUSE_WRITE		=	0xD4
};

extern uint8_t keyboard_ctrl_readStatus();
extern void keyboard_ctrl_sendCmd (uint8_t cmd);
extern uint8_t keyboard_enc_readBuffer();
extern void keyboard_enc_sendCmd(uint8_t cmd);

extern bool keyboard_getScrollLock();
extern bool keyboard_getNumLock();
extern bool keyboard_getCapsLock();
extern bool keyboard_getCtrl();
extern bool keyboard_getAlt();
extern bool keyboard_getShift();
extern void keyboard_ignoreResend();
extern bool keyboard_checkResend();
extern bool keyboard_getDiagnosticRes();
extern bool keyboard_getBatRes();
extern uint8_t keyboard_getLastScan();

extern enum KEYCODE keyboard_getLastKey();
extern void keyboard_discardLastKey();
extern char keyboard_key2ascii(enum KEYCODE code);

extern void keyboard_disable();
extern void keyboard_enable();
extern bool keyboard_isDisabled();

extern void keyboard_resetSystem();
extern bool keyboard_selfTest();

extern void keyboard_init(int irq);
#endif