#ifndef _CB_KBD_KBDERR_H_
#define _CB_KBD_KBDERR_H_

enum keyboard_ERROR {
	keyboard_ERR_BUF_OVERRUN    =	0,
	keyboard_ERR_ID_RET			=	0x83AB,
	keyboard_ERR_BAT			=	0xAA,
	keyboard_ERR_ECHO_RET		=	0xEE,
	keyboard_ERR_ACK			=	0xFA,
	keyboard_ERR_BAT_FAILED		=	0xFC,
	keyboard_ERR_DIAG_FAILED	=	0xFD,
	keyboard_ERR_RESEND_CMD		=	0xFE,
	keyboard_ERR_KEY			=	0xFF
};

#endif