#include "drivers/keyboard.h"
#include "kernel/common.h"
#include <stdint.h>
#include <cboolean.h>

#define KBD_KEYMAP_SIZE 512

#define KBD_ENCORDER_INPUT_BUFF 0x60
#define KBD_ENCODER_CMD_REG     0x60
#define KBD_CTRL_STATS_REG      0x64
#define KBD_CTRL_CMD_REG        0x64

#define KBD_CTRL_STATS_MASK_OUT_BUFF    0b00000001  // 1
#define KBD_CTRL_STATS_MASK_IN_BUFF     0b00000010  // 2
#define KBD_CTRL_STATS_MASK_SYSTEM      0b00000100  // 4
#define KBD_CTRL_STATS_MASK_CMD_DATA    0b00001000  // 8
#define KBD_CTRL_STATS_MASK_LOCKED      0b00010000  // 16
#define KBD_CTRL_STATS_MASK_AUX_BUFF    0b00100000  // 32
#define KBD_CTRL_STATS_MASK_TIMEOUT     0b01000000  // 64
#define KBD_CTRL_STATS_MASK_PARITY      0b10000000  // 128

/*enum kbd_encoder_io {
    kbd_encoder_inputBuff   = 0x60,
    kbd_encoder_cmdRegister = 0x60
};

enum kbd_ctrl_io {
    kbd_ctrl_statsRegister  = 0x64,
    kbd_ctrl_cmdRegister    = 0x64
};*/

void _kbd_io_wait() {
    // This function waits for keyboards's input buffer to be clear.

    while (1) {
        if((kbd_ctrl_getStatus() & KBD_CTRL_STATS_MASK_IN_BUFF) == 0x00)
            break;
    }
    
}

uint8_t kbd_ctrl_getStatus() {
    return inb(KBD_CTRL_STATS_REG);
}

uint8_t kbd_encoder_readBuff() {
    return inb(KBD_ENCORDER_INPUT_BUFF);
}

void kbd_encoder_sendCmd(uint8_t __cmd) {
    _kbd_io_wait();
    outb(KBD_ENCODER_CMD_REG, __cmd);
}

void kbd_encoder_sendPacket(uint8_t __cmd, uint8_t __data) {
    kbd_encoder_sendCmd(__cmd);
    kbd_encoder_sendCmd(__data);
}



#define KBD_ENCODER_CMD_SET_LEDS        0xED
#define KBD_ENCODER_CMD_ECHO            0xEE
#define KBD_ENCODER_CMD_ASCS            0xF0 // Alternate scan code set
#define KBD_ENCODER_CMD_KBD_ID          0xF2
#define KBD_ENCODER_CMD_DELAY_RATE      0xF3
#define KBD_ENCODER_CMD_ENABLE          0xF4
#define KBD_ENCODER_CMD_RST_WAIT        0xF5
#define KBD_ENCODER_CMD_RST_SCAN        0xF6
#define KBD_ENCODER_CMD_AUTREP_ALL      0xF7
#define KBD_ENCODER_CMD_SMB_ALL         0xF8 // set all keys to send make code and to send
                                             // break code
#define KBD_ENCODER_CMD_MCONLY_ALL      0xF9 // set all keys to generate only make code
#define KBD_ENCODER_CMD_AUTREP_MB_ALL   0xFA // dry sll keys to autorep. and generate make
                                             // codes and break codes
#define KBD_ENCODER_CMD_AUTREP          0xFB
#define KBD_ENCODER_CMD_MB              0xFC // set a single key to generate make codes and
                                             // to generate break codes
#define KBD_ENCODER_CMD_B               0xFD // set a single key to only generate break 
                                             // codes
#define KBD_ENCODER_CMD_RESEND_LAST     0xFE
#define KBD_ENCODER_CMD_RST_SELF_TEST   0xFF



void kbd_setLeds(   bool __n, // NumLock LED
                    bool __c, // CapsLock LED
                    bool __s  // ScrollLock LED
                ) {
    // Sets keyboard LED indicators.

    uint8_t data;

    data = (__s) ? (data | 1) : (data & 1);
    data = (__n) ? (__n  | 2) : (__n  & 2);
    data = (__c) ? (__n  | 4) : (__n  & 4);

    kbd_encoder_sendPacket(KBD_ENCODER_CMD_SET_LEDS, data);
}

/*void kbd_setAlternateScancodeSet() {
    // ...
}

void kbd:repRate(uint8_t __r) {
    // ...
}*/

#define KBD_ENCODER_RETURN_INT_BUFF_OVERRUN 0x00
#define KBD_ENCODER_RETURN_KBD_ID           0x83AB
#define KBD_ENCODER_RETURN_BAT              0xAA
#define KBD_ENCODER_RETURN_ECHO             0xEE
#define KBD_ENCODER_RETURN_ACK              0xFA
#define KBD_ENCODER_RETURN_BAT_FAIL         0xFC
#define KBD_ENCODER_RETURN_RESEND_REQ       0xFE
#define KBD_ENCODER_RETURN_ERROR            0xFF

