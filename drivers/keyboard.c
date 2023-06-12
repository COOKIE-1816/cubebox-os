#include "kernel/common.h"
#include "drivers/keyboard.h"
#include "drivers/keyboard/kbderr.h"
#include "drivers/keyboard/scancodes.h"
#include "drivers/keyboard/keycode.h"

//#include "cboolean.h"

const int INVALID_SCANCODE = 0;

char _scancode;
bool _numlock, 
            _scrolllock, 
            _capslock;
bool _shift, 
            _alt, 
            _ctrl;
int  _keyboard_error =      0;
bool _keyboard_bat_res =    false;
bool _keyboard_diag_res =   false;
bool _keyboard_resend_res = false;
bool _keyboard_disable =    false;

uint8_t		keyboard_ctrl_readStatus ();
void		keyboard_ctrl_sendCmd (uint8_t);
uint8_t		keyboard_end_readBuffer ();
void		keyboard_enc_send_cmd (uint8_t);




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

inline bool keyboard_getScrollLock() {
	return _scrolllock;
}

inline bool keyboard_getNumLock() {
	return _numlock;
}

inline bool keyboard_getCapsLock() {
	return _capslock;
}

inline bool keyboard_getCtrl()	{
	return _ctrl;
}

inline bool keyboard_getAlt() {
	return _alt;
}

inline bool keyboard_getShift() {
	return _shift;
}

inline void keyboard_ignoreResend() {
	_keyboard_resend_res = false;
}

inline bool keyboard_checkResend() {
	return _keyboard_resend_res;
}

inline bool keyboard_getDiagnosticRes() {
	return _keyboard_diag_res;
}

inline bool keyboard_getBatRes() {
	return _keyboard_bat_res;
}

inline uint8_t keyboard_getLastScan() {
	return _scancode;
}

inline void i86_keyboard_irq (){
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

inline KEYCODE keyboard_get_last_key () {
	return (_scancode != INVALID_SCANCODE) ? ((KEYCODE) _keyboard_scancode_std[_scancode]) : (KEY_UNKNOWN);
}

inline void keyboard_discard_last_key () {
	_scancode = INVALID_SCANCODE;
}

inline char keyboard_key_to_ascii (KEYCODE code) {
	uint8_t key = code;

	if (isascii (key)) {
		if (_shift || _capslock) {
			if (key >= 'a' && key <= 'z')
				key -= 32;
		}

		if (_shift && !_capslock)
			if (key >= '0' && key <= '9')
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

						case KEY_LEFTBRACKET :
							key = KEY_LEFTCURL;
							break;

						case KEY_RIGHTBRACKET :
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

inline void keyboard_disable () {
	keyboard_ctrl_sendCmd (keyboard_CTRL_CMD_DISABLE);
	_keyboard_disable = true;
}

inline void keyboard_enable () {
	keyboard_ctrl_sendCmd (keyboard_CTRL_CMD_ENABLE);
	_keyboard_disable = false;
}

inline bool keyboard_isDisabled () {
	return _keyboard_disable;
}

inline void keyboard_resetSystem () {
	keyboard_ctrl_sendCmd (keyboard_CTRL_CMD_WRITE_OUT_PORT);
	keyboard_enc_send_cmd (0xfe);
}

inline bool keyboard_selfTest () {
	keyboard_ctrl_sendCmd (keyboard_CTRL_CMD_SELF_TEST);

	while(1) {
		if (keyboard_ctrl_readStatus () & keyboard_CTRL_STATS_MASK_OUT_BUF)
			break;
	}

	return (keyboard_end_readBuffer () == 0x55) ? true : false;
}

inline void keyboard_init(int irq) {
	setvect(irq, i86_keyboard_irq);

	_keyboard_bat_res = true;
	_scancode = 0;

	_numlock = _scrolllock = _capslock = false;
	keyboard_leds_set (false, false, false);

	_shift = _alt = _ctrl = false;
}
