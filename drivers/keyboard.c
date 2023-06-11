#include "kernel/common.h"
#include "drivers/keyboard.h"
#include "drivers/keyboard/kbderr.h"
#include "drivers/keyboard/scancodes.h"

//#include "cboolean.h"

static char _scancode;
static bool _numlock, 
            _scrolllock, 
            _capslock;
static bool _shift, 
            _alt, 
            _ctrl;
static int  _keyboard_error =      0;
static bool _keyboard_bat_res =    false;
static bool _keyboard_diag_res =   false;
static bool _keyboard_resend_res = false;
static bool _keyboard_disable =    false;

const int INVALID_SCANCODE = 0;

static int _keyboard_scancode_std [] = {
	KEY_UNKNOWN,	//0
	KEY_ESCAPE,		//1
	KEY_1,			//2
	KEY_2,			//3
	KEY_3,			//4
	KEY_4,			//5
	KEY_5,			//6
	KEY_6,			//7
	KEY_7,			//8
	KEY_8,			//9
	KEY_9,			//0xa
	KEY_0,			//0xb
	KEY_MINUS,		//0xc
	KEY_EQUAL,		//0xd
	KEY_BACKSPACE,	//0xe
	KEY_TAB,		//0xf
	KEY_Q,			//0x10
	KEY_W,			//0x11
	KEY_E,			//0x12
	KEY_R,			//0x13
	KEY_T,			//0x14
	KEY_Y,			//0x15
	KEY_U,			//0x16
	KEY_I,			//0x17
	KEY_O,			//0x18
	KEY_P,			//0x19
	KEY_LEFTBRACKET,//0x1a
	KEY_RIGHTBRACKET,//0x1b
	KEY_RETURN,		//0x1c
	KEY_LCTRL,		//0x1d
	KEY_A,			//0x1e
	KEY_S,			//0x1f
	KEY_D,			//0x20
	KEY_F,			//0x21
	KEY_G,			//0x22
	KEY_H,			//0x23
	KEY_J,			//0x24
	KEY_K,			//0x25
	KEY_L,			//0x26
	KEY_SEMICOLON,	//0x27
	KEY_QUOTE,		//0x28
	KEY_GRAVE,		//0x29
	KEY_LSHIFT,		//0x2a
	KEY_BACKSLASH,	//0x2b
	KEY_Z,			//0x2c
	KEY_X,			//0x2d
	KEY_C,			//0x2e
	KEY_V,			//0x2f
	KEY_B,			//0x30
	KEY_N,			//0x31
	KEY_M,			//0x32
	KEY_COMMA,		//0x33
	KEY_DOT,		//0x34
	KEY_SLASH,		//0x35
	KEY_RSHIFT,		//0x36
	KEY_KP_ASTERISK,//0x37
	KEY_RALT,		//0x38
	KEY_SPACE,		//0x39
	KEY_CAPSLOCK,	//0x3a
	KEY_F1,			//0x3b
	KEY_F2,			//0x3c
	KEY_F3,			//0x3d
	KEY_F4,			//0x3e
	KEY_F5,			//0x3f
	KEY_F6,			//0x40
	KEY_F7,			//0x41
	KEY_F8,			//0x42
	KEY_F9,			//0x43
	KEY_F10,		//0x44
	KEY_KP_NUMLOCK,	//0x45
	KEY_SCROLLLOCK,	//0x46
	KEY_HOME,		//0x47
	KEY_KP_8,		//0x48	//keypad up arrow
	KEY_PAGEUP,		//0x49
	KEY_KP_2,		//0x50	//keypad down arrow
	KEY_KP_3,		//0x51	//keypad page down
	KEY_KP_0,		//0x52	//keypad insert key
	KEY_KP_DECIMAL,	//0x53	//keypad delete key
	KEY_UNKNOWN,	//0x54
	KEY_UNKNOWN,	//0x55
	KEY_UNKNOWN,	//0x56
	KEY_F11,		//0x57
	KEY_F12			//0x58
};

inline uint8_t keyboard_ctrl_readStatus() {
	return inb (keyboard_CTRL_STATS_REG);
}

inline void keyboard_ctrl_sendCmd (uint8_t cmd) {
	while (1) {
        if((keyboard_ctrl_readStatus() & keyboard_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
    }
 
	outb(keyboard_CTRL_CMD_REG, cmd);
}

inline uint8_t keyboard_enc_readBuffer() {
	return inb(keyboard_ENC_INPUT_BUF);
}

inline void keyboard_enc_sendCmd(uint8_t cmd) {
	while (1) {
        if ((keyboard_ctrl_readStatus() & keyboard_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
    }
 
	outb(keyboard_ENC_CMD_REG, cmd);
}

bool keyboard_getScrollLock() {
	return _scrolllock;
}

bool keyboard_getNumLock() {
	return _numlock;
}

bool keyboard_getCapsLock() {
	return _capslock;
}

bool keyboard_getCtrl()	{
	return _ctrl;
}

bool keyboard_getAlt() {
	return _alt;
}

bool keyboard_getShift() {
	return _shift;
}

void keyboard_ignoreResend() {
	_keyboard_resend_res = false;
}

bool keyboard_checkResend() {
	return _keyboard_resend_res;
}

bool keyboard_getDiagnosticRes() {
	return _keyboard_diag_res;
}

bool keyboard_getBatRes() {
	return _keyboard_bat_res;
}

uint8_t keyboard_getLastScan() {
	return _scancode;
}

void i86_keyboard_irq (){
	asm volatile(
        "add $12, %esp\n"
        "pusha\n"
        "cli\n"
    );

	static bool _extended = false;
	int code = 0;

	if (keyboard_ctrl_readStatus () & keyboard_CTRL_STATS_MASK_OUT_BUF) {
		code = keyboard_enc_readBuffer ();

		if (code == 0xE0 || code == 0xE1) {
            _extended = true;
        } else {
			_extended = false;

			if (code & 0x80) {
                code -= 0x80;
				int key = _keyboard_scancode_std [code];

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
				int key = _keyboard_scancode_std [code];

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
						keyboard_leds_set (_numlock, _capslock, _scrolllock);

						break;

					case KEY_KP_NUMLOCK:
						_numlock = (_numlock) ? false : true;
						keyboard_leds_set (_numlock, _capslock, _scrolllock);

						break;

					case KEY_SCROLLLOCK:
						_scrolllock = (_scrolllock) ? false : true;
						keyboard_leds_set (_numlock, _capslock, _scrolllock);

						break;
				}
			}
		}

		switch (code) {
			case keyboard_ERR_BAT_FAILED:
				_keyboard_bat_res = false;

				break;

			case keyboard_ERR_DIAG_FAILED:
				_keyboard_diag_res = false;

				break;

			case keyboard_ERR_RESEND_CMD:
				_keyboard_resend_res = true;

				break;
		}
	}

	//interruptdone(0);

	//asm(" sti");
	/*asm(
        "sti\n"
        "pop edi\n"
        "pop esi\n"
        "pop ebp\n"
        "pop ebx\n"
        "pop edx\n"
        "pop ecx\n"
        "pop eax\n"
        "ret\n"
        :
        :
        : "%eax", "%ecx", "%edx", "%ebx", "%ebp", "%esi", "%edi"
    );*/

    i86_keyboard_irq_asm();
}
