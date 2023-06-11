#ifndef _CB_KEYBOARD_H_
#define _CB_KEYBOARD_H_

#include <stdint.h>
#include "cboolean.h"

//#define keyboard_CTRL_STATS_REG 0x64

/*
static char _scancode;
static bool _numlock, _scrolllock, _capslock;
static bool _shift, _alt, _ctrl;
static int _kkybrd_error = 0;
static bool _kkybrd_bat_res = false;
static bool _kkybrd_diag_res = false;
static bool _kkybrd_resend_res = false;
static bool _kkybrd_disable = false;
*/

//const int INVALID_SCANCODE = 0;


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

#endif