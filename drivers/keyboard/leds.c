#include "kernel/common.h"
#include "drivers/keyboard/leds.h"
#include "drivers/keyboard.h"

inline void keyboard_leds_set(bool n, bool c, bool s) {
    uint8_t data = 0;

	data = (s) ? (data  | 1) : (data & 1);
	data = (n) ? (n     | 2) : (n    & 2);
	data = (c) ? (n     | 4) : (n    & 4);
 
	keyboard_enc_sendCmd(keyboard_ENC_CMD_SET_LED);
	keyboard_enc_sendCmd(data);
}