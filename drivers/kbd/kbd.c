#include "kbd.h"
#include "../../kernel/kernel.h"


void kbd_ioWait() {
	while (1) {
		if ((kbd_ctrl_getStatus() & kbd_CTRL_STATS_MASK_IN_BUF) == 0) {
			break;
		}
	}
}

enum kbd_ENCODER_IO {
	kbd_ENC_INPUT_BUF = 0x60,
	kbd_ENC_CMD_REG = 0x60
};

enum kbd_ENC_CMDS {
	kbd_ENC_CMD_SET_LED = 0xED,
	kbd_ENC_CMD_ECHO = 0xEE,
	kbd_ENC_CMD_SCAN_CODE_SET = 0xF0,
	kbd_ENC_CMD_ID = 0xF2,
	kbd_ENC_CMD_AUTODELAY = 0xF3,
	kbd_ENC_CMD_ENABLE = 0xF4,
	kbd_ENC_CMD_RESETWAIT = 0xF5,
	kbd_ENC_CMD_RESETSCAN = 0xF6,
	kbd_ENC_CMD_ALL_AUTO = 0xF7,
	kbd_ENC_CMD_ALL_MAKEBREAK = 0xF8,
	kbd_ENC_CMD_ALL_MAKEONLY = 0xF9,
	kbd_ENC_CMD_ALL_MAKEBREAK_AUTO = 0xFA,
	kbd_ENC_CMD_SINGLE_AUTOREPEAT = 0xFB,
	kbd_ENC_CMD_SINGLE_MAKEBREAK = 0xFC,
	kbd_ENC_CMD_SINGLE_BREAKONLY = 0xFD,
	kbd_ENC_CMD_RESEND = 0xFE,
	kbd_ENC_CMD_RESET = 0xFF
};

enum kbd_CTRL_IO {

	kbd_CTRL_STATS_REG = 0x64,
	kbd_CTRL_CMD_REG = 0x64
};

enum kbd_CTRL_STATS_MASK {
	kbd_CTRL_STATS_MASK_OUT_BUF = 1,		//00000001
	kbd_CTRL_STATS_MASK_IN_BUF = 2,		//00000010
	kbd_CTRL_STATS_MASK_SYSTEM = 4,		//00000100
	kbd_CTRL_STATS_MASK_CMD_DATA = 8,		//00001000
	kbd_CTRL_STATS_MASK_LOCKED = 0x10,	//00010000
	kbd_CTRL_STATS_MASK_AUX_BUF = 0x20,	//00100000
	kbd_CTRL_STATS_MASK_TIMEOUT = 0x40,	//01000000
	kbd_CTRL_STATS_MASK_PARITY = 0x80	//10000000
};

enum kbd_CTRL_CMDS {
	kbd_CTRL_CMD_READ = 0x20,
	kbd_CTRL_CMD_WRITE = 0x60,
	kbd_CTRL_CMD_SELF_TEST = 0xAA,
	kbd_CTRL_CMD_INTERFACE_TEST = 0xAB,
	kbd_CTRL_CMD_DISABLE = 0xAD,
	kbd_CTRL_CMD_ENABLE = 0xAE,
	kbd_CTRL_CMD_READ_IN_PORT = 0xC0,
	kbd_CTRL_CMD_READ_OUT_PORT = 0xD0,
	kbd_CTRL_CMD_WRITE_OUT_PORT = 0xD1,
	kbd_CTRL_CMD_READ_TEST_INPUTS = 0xE0,
	kbd_CTRL_CMD_SYSTEM_RESET = 0xFE,
	kbd_CTRL_CMD_MOUSE_DISABLE = 0xA7,
	kbd_CTRL_CMD_MOUSE_ENABLE = 0xA8,
	kbd_CTRL_CMD_MOUSE_PORT_TEST = 0xA9,
	kbd_CTRL_CMD_MOUSE_WRITE = 0xD4
};

// scan error codes ------------------------------------------

enum kbd_ERROR {
	kbd_ERR_BUF_OVERRUN = 0,
	kbd_ERR_ID_RET = 0x83AB,
	kbd_ERR_BAT = 0xAA,	//note: can also be L. shift key make code
	kbd_ERR_ECHO_RET = 0xEE,
	kbd_ERR_ACK = 0xFA,
	kbd_ERR_BAT_FAILED = 0xFC,
	kbd_ERR_DIAG_FAILED = 0xFD,
	kbd_ERR_RESEND_CMD = 0xFE,
	kbd_ERR_KEY = 0xFF
};

static char _scancode;
static bool _numlock, _scrolllock, _capslock;
static bool _shift, _alt, _ctrl;
static int _kbd_error = 0;
static bool _kbd_bat_res = false;
static bool _kbd_diag_res = false;
static bool _kbd_resend_res = false;
static bool _kbd_disable = false;

static int _kbd_scancode_std[] = {
	KEY_UNKNOWN, KEY_ESCAPE, KEY_1,	KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,	KEY_0,			
	KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_TAB, KEY_Q, KEY_W,	KEY_E, KEY_R, KEY_T, KEY_Y,			
	KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACKET, KEY_RIGHTBRACKET, KEY_RETURN, KEY_LCTRL, KEY_A,			
	KEY_S, KEY_D, KEY_F, KEY_G,	KEY_H, KEY_J, KEY_K, KEY_L,	KEY_SEMICOLON, KEY_QUOTE, KEY_GRAVE,		
	KEY_LSHIFT,	KEY_BACKSLASH, KEY_Z, KEY_X, KEY_C,	KEY_V, KEY_B, KEY_N, KEY_M,	KEY_COMMA, KEY_DOT,		
	KEY_SLASH, KEY_RSHIFT, KEY_KP_ASTERISK, KEY_RALT, KEY_SPACE, KEY_CAPSLOCK, KEY_F1, KEY_F2,			
	KEY_F3,	KEY_F4,	KEY_F5,	KEY_F6,	KEY_F7,	KEY_F8,	KEY_F9,	KEY_F10, KEY_KP_NUMLOCK,	
	KEY_SCROLLLOCK,	KEY_HOME, KEY_KP_8,	KEY_PAGEUP,	KEY_KP_2, KEY_KP_3,	KEY_KP_0, KEY_KP_DECIMAL,	
	KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN, KEY_F11,	KEY_F12
};

const int INVALID_SCANCODE = 0;

uint8_t kbd_ctrl_getStatus() {
	return inportb(kbd_CTRL_STATS_REG);
}

void kbd_ctrl_sendCommand(uint8_t cmd) {
	kbd_ioWait();
	outportb(kbd_CTRL_CMD_REG, cmd);
}

uint8_t kbd_encoder_readBuffer() {
	return inportb(kbd_ENC_INPUT_BUF);
}

void kbd_encoder_sendCommand(uint8_t cmd) {
	kbd_ioWait();
	outportb(kbd_ENC_CMD_REG, cmd);
}

void _cdecl i86_kbd_irq() {
	_asm add esp, 12
	_asm pushad
	_asm cli

	static bool _extended = false;

	int code = 0;

	if (kbd_ctrl_getStatus() & kbd_CTRL_STATS_MASK_OUT_BUF) {
		code = kbd_encoder_readBuffer();

		if (code == 0xE0 || code == 0xE1) {
			_extended = true;
		} else {
			_extended = false;

			if (code & 0x80) {
				code -= 0x80;
				int key = _kbd_scancode_std[code];

				switch (key) {
					case KEY_LCTRL:
					case KEY_RCTRL:
						_ctrl = false;
						break;

					case KEY_LSHIFT:
					case KEY_RSHIFT:
						_shift = false;
						break;

					case KEY_LALT:
					case KEY_RALT:
						_alt = false;
						break;
				}
			} else {
				_scancode = code;
				int key = _kbd_scancode_std[code];

				switch (key) {
					case KEY_LCTRL:
					case KEY_RCTRL:
						_ctrl = true;
						break;

					case KEY_LSHIFT:
					case KEY_RSHIFT:
						_shift = true;
						break;

					case KEY_LALT:
					case KEY_RALT:
						_alt = true;
						break;

					case KEY_CAPSLOCK:
						_capslock = (_capslock) ? false : true;
						kbd_setLeds(_numlock, _capslock, _scrolllock);
						break;

					case KEY_KP_NUMLOCK:
						_numlock = (_numlock) ? false : true;
						kbd_setLeds(_numlock, _capslock, _scrolllock);
						break;

					case KEY_SCROLLLOCK:
						_scrolllock = (_scrolllock) ? false : true;
						kbd_setLeds(_numlock, _capslock, _scrolllock);
						break;
				}
			}
		}

		switch (code) {
			case kbd_ERR_BAT_FAILED:
				_kbd_bat_res = false;
				break;

			case kbd_ERR_DIAG_FAILED:
				_kbd_diag_res = false;
				break;

			case kbd_ERR_RESEND_CMD:
				_kbd_resend_res = true;
				break;
		}
	}

	//interruptdone(0);

	_asm sti
	_asm popad
	_asm iretd
}

bool kbd_getScrollLock() {
	return _scrolllock;
}

bool kbd_getNumLock() {
	return _numlock;
}

bool kbd_getCapsLock() {
	return _capslock;
}

bool kbd_getCtrlKey() {
	return _ctrl;
}

bool kbd_getAltKey() {
	return _alt;
}

bool kbd_getShiftKey() {
	return _shift;
}

void kbd_resend_ignore() {
	_kbd_resend_res = false;
}

bool kbd_resend_check() {
	return _kbd_resend_res;
}

bool kbd_diagnostic_getResult() {
	return _kbd_diag_res;
}

bool kbd_bat_getResult() {
	return _kbd_bat_res;
}

uint8_t kbd_getLastScan() {
	return _scancode;
}

void kbd_setLeds(bool num, bool caps, bool scroll) {
	uint8_t data = 0;

	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);

	kbd_encoder_sendCommand(kbd_ENC_CMD_SET_LED);
	kbd_encoder_sendCommand(data);
}

KEYCODE kbd_getLastKey() {
	return (_scancode != INVALID_SCANCODE) ? ((KEYCODE)_kbd_scancode_std[_scancode]) : (KEY_UNKNOWN);
}

void kbd_discardLastKey() {
	_scancode = INVALID_SCANCODE;
}

char kbd_key2ascii(KEYCODE code) {
	uint8_t key = code;

	if (isascii(key)) {
		if (_shift || _capslock)
			if (key >= 'a' && key <= 'z') {
				key -= 32;
			}

		if (_shift && !_capslock)
			if (key >= '0' && key <= '9') {
				switch (key) {
					case '0':
						key = KEY_RIGHTPARENTHESIS;
						break;
					case '1':
						key = KEY_EXCLAMATION;
						break;
					case '2':
						key = KEY_AT;
						break;
					case '3':
						key = KEY_EXCLAMATION;
						break;
					case '4':
						key = KEY_HASH;
						break;
					case '5':
						key = KEY_PERCENT;
						break;
					case '6':
						key = KEY_CARRET;
						break;
					case '7':
						key = KEY_AMPERSAND;
						break;
					case '8':
						key = KEY_ASTERISK;
						break;
					case '9':
						key = KEY_LEFTPARENTHESIS;
						break;
				}
			} else {
				switch (key) {
					case KEY_COMMA:
						key = KEY_LESS;
						break;

					case KEY_DOT:
						key = KEY_GREATER;
						break;

					case KEY_SLASH:
						key = KEY_QUESTION;
						break;

					case KEY_SEMICOLON:
						key = KEY_COLON;
						break;

					case KEY_QUOTE:
						key = KEY_QUOTEDOUBLE;
						break;

					case KEY_LEFTBRACKET:
						key = KEY_LEFTCURL;
						break;

					case KEY_RIGHTBRACKET:
						key = KEY_RIGHTCURL;
						break;

					case KEY_GRAVE:
						key = KEY_TILDE;
						break;

					case KEY_MINUS:
						key = KEY_UNDERSCORE;
						break;

					case KEY_PLUS:
						key = KEY_EQUAL;
						break;

					case KEY_BACKSLASH:
						key = KEY_BAR;
						break;
				}
			}

		return key;
	}

	return 0;
}

void kbd_disable() {
	kbd_ctrl_sendCommand(kbd_CTRL_CMD_DISABLE);
	_kbd_disable = true;
}

void kbd_enable() {
	kbd_ctrl_sendCommand(kbd_CTRL_CMD_ENABLE);
	_kbd_disable = false;
}

bool kbd_isDisabled() {
	return _kbd_disable;
}

void kbd_systemReset() {
	kbd_ctrl_sendCommand(kbd_CTRL_CMD_WRITE_OUT_PORT);
	kbd_encoder_sendCommand(0xfe);
}

bool kbd_selfTest() {
	kbd_ctrl_sendCommand(kbd_CTRL_CMD_SELF_TEST);
	kbd_ioWait();

	return (kbd_encoder_readBuffer() == 0x55) ? true : false;
}

void kbd_init(int irq) {
	setvect(irq, i86_kbd_irq);

	_kbd_bat_res = true;
	_scancode = 0;

	_numlock = _scrolllock = _capslock = false;
	kbd_setLeds(false, false, false);

	_shift = _alt = _ctrl = false;
}