#include "drivers/keyboard.h"
#include "drivers/pci.h"

#include "kernel/common.h"
#include "kernel/tty.h"
#include "kernel/kdrivers.h"
//#include "kernel/interrupt/idt.h"
#include "kernel/interrupt/irq.h"

#include <stdint.h>
#include <cboolean.h>

#define KBD_KEYMAP_SIZE 512

uint8_t kbdIRQ = 1;

kdriver _kbd;


#define KBD_ENCORDER_INPUT_BUFF         0x60 // 
#define KBD_ENCODER_CMD_REG             0x60 //
#define KBD_CTRL_STATS_REG              0x64 //
#define KBD_CTRL_CMD_REG                0x64 //

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

uint8_t kbd_ctrl_getStatus() {
    return inb(KBD_CTRL_STATS_REG);
}

void _kbd_io_wait() {
    // This function waits for keyboards's input buffer to be clear.

    while (1) {
        if((kbd_ctrl_getStatus() & KBD_CTRL_STATS_MASK_IN_BUFF) == 0x00)
            break;
    }
    
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


typedef struct kbd_kbdState {
    bool nl; // ===========
    bool cl; //    Lock keys status
    bool sl; // ===========

    bool shift;
    bool alt;
    bool ctrl;

    bool special;

    bool pause;
} kbd_kbdState;

kbd_kbdState kbd_state;



bool *kbd_getLockKeys() {
    static bool state[3];

    state[0] = kbd_state.nl;
    state[1] = kbd_state.cl;
    state[2] = kbd_state.sl;

    return  state;
}

bool kbd_getShift() {
    return kbd_state.shift;
}

bool kbd_getAlt() {
    return kbd_state.alt;
}

bool kbd_getCtrl() {
    return kbd_state.ctrl;
}

bool kbd_getSpecial() {
    return kbd_state.special;
}

bool kbd_getPause() {
    return kbd_state.pause;
}





void kbd_setLeds(   bool __n, // NumLock LED
                    bool __c, // CapsLock LED
                    bool __s  // ScrollLock LED
                ) {
    // Sets keyboard LED indicators.
    // * NOTE: Only changes indicator status. Does not toggle lock keys.

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
#define KBD_ENCODER_RETURN_RESEND_REQ       0xFE // This return code is returned to request resend
#define KBD_ENCODER_RETURN_ERROR            0xFF

bool kbd_return_isKeypress(uint8_t __return) {
    // Returns a boolean. Boolean value depends on that if return code is a keypress return code.

    return  (__return > 0x00 && __return < 0x59) || 
            (__return > 0x80 && __return < 0xD9);

    /*
        ^^^^^^^^^^^^^
        RETURN CODES EXPLANATION

        The 0x01, ..., 0x58, 0x81 ..., 0xD8 are keyboard keypress return codes. They are return when
        specific key is pressed. Thats what their values depends on.

            Online ref.: http://www.brokenthorn.com/Resources/OSDev19.html
        
        0x00 because 0x01 - 0x01 is 0x00
        0x59 because 0x58 + 0x01 is 0x59
        0x80 because 0x81 - 0x01 is 0x80
        0xD9 because 0xD8 + 0x01 is 0xD9
    */
}

#define KBD_CTRL_CMD_READ_CMD_BYTE  0x20
#define KBD_CTRL_CMD_WRITE_CMD_BYTE 0x60
#define KBD_CTRL_CMD_SELF_TEST      0xAA
#define KBD_CTRL_CMD_INTERFACE_TEST 0xAB
#define KBD_CTRL_CMD_DISABLE        0xAD
#define KBD_CTRL_CMD_ENABLE         0xAE
#define KBD_CTRL_CMD_READ_IN        0xC0
#define KBD_CTRL_CMD_READ_OUT       0xD0
#define KBD_CTRL_CMD_WRITE_OUT      0xD1
#define KBD_CTRL_CMD_READ_TEST_IN   0xE0
#define KBD_CTRL_CMD_SYSTEM_RST     0xFE

void kbd_ctrl_sendCmd(uint8_t __cmd) {
    _kbd_io_wait();
    outb(KBD_CTRL_CMD_REG, __cmd);
}

/*#define KBD_SELF_TEST_OK    true
#define KBD_SELF_TEST_FAIL  false*/

bool kbd_selfTest() {
    // Performs a keyboard self test.

    kbd_ctrl_sendCmd(KBD_CTRL_CMD_SELF_TEST);
    _kbd_io_wait();

    return kbd_encoder_readBuff() == 0x55;
}


/*#define KBD_INTERFACE_TEST_OK                   0x00
#define KBD_INTERFACE_TEST_ERR_CLL_STUCK_LOW    0x01
#define KBD_INTERFACE_TEST_ERR_CLL_STUCK_HIGH   0x02
#define KBD_INTERFACE_TEST_ERR_DATAL_STUCK_HIGH 0x03
#define KBD_INTERFACE_TEST_ERR_GENERAL          0xFF*/

uint8_t kbd_interfaceTest() {
    // Performs a keyboard interface test.

    uint8_t result;

    kbd_ctrl_sendCmd(KBD_CTRL_CMD_INTERFACE_TEST);
    _kbd_io_wait();

    result = kbd_encoder_readBuff();

    switch (result) {
        case KBD_INTERFACE_TEST_OK:
            tty_writeString("Kbd: interface test: Interface test OK.\n");
            break;
        
        case KBD_INTERFACE_TEST_ERR_CLL_STUCK_LOW:
            tty_writeString("Kbd: interface test: err: Clock line stuck low.\n");
            break;
        
        case KBD_INTERFACE_TEST_ERR_CLL_STUCK_HIGH:
            tty_writeString("Kbd: interface test: err: Clock line stuck high.\n");
            break;

        case KBD_INTERFACE_TEST_ERR_DATAL_STUCK_HIGH:
            tty_writeString("Kbd: interface test: err: Data line stuck high\n");
            break;

        default:
            tty_writeString("Kbd: interface test: Unrecognized, unknown or general error.\n");
            break;
    }

    return result;
}

bool _kbd_enabled;

void kbd_enable() {
    kbd_ctrl_sendCmd(KBD_CTRL_CMD_ENABLE);
    _kbd_enabled = true;
}

void kbd_disable() {
    kbd_ctrl_sendCmd(KBD_CTRL_CMD_DISABLE);
    _kbd_enabled = false;
}

void kbd_setEnabled(bool __enable) {
    if(__enable == _kbd_enabled)
        return;
    
    if(__enable)
        kbd_enable();
    
    kbd_disable();
}


uint8_t kbd_ctrl_readOutBuff() {
    return inb(KBD_CTRL_STATS_MASK_OUT_BUFF);
}



void kbd_writeOutPort(uint8_t __value) {
    outb(0x60, __value);
}


void kbd_resetSystem() {
    kbd_ctrl_sendCmd(KBD_CTRL_CMD_SYSTEM_RST);
    kbd_encoder_sendCmd(0xfe);
}

uint8_t kbd_lastScancode;

uint8_t kbd_getLast() {
    return kbd_lastScancode;
}

uint8_t _kbd_scancode;

void kbd_irqHandler() {
    _kbd_scancode = inb(KBD_ENCORDER_INPUT_BUFF);

    tty_writeString("kbdIrq\n");

    switch (_kbd_scancode) {
        // === SHIFT KEYS ===
        case 0x2A:
        case 0x36:
            kbd_state.shift = true;
            break;
        
        case 0xAA:
        case 0xB6:
            kbd_state.shift = false;
            break;

        // === LOCK KEYS ===
        case 0x3A:
            kbd_state.cl = !kbd_state.cl;
            break;
        
        case 0x45:
            kbd_state.nl = !kbd_state.nl;
            break;

        /*case 0x46:
            kbd_state.sl = !kbd_state.sl;
            break;*/

        // TODO: Implement pause break later. Only pause when printing on screen is in process.
        // TODO: Implement other keys.

        default:
            break;
    }

    kbd_lastScancode = _kbd_scancode;

    // * Send EOI signal to PIC
    outb(0x20, 0x20);
}

int kbd_init() {
    _kbd.name = "Standard PS2 keyboard";
    kdriver_statusMsg_create(_kbd);

    kbd_lastScancode = 0x00;

    kbd_state.nl =      false;
    kbd_state.cl =      false;
    kbd_state.sl =      false;
    kbd_state.alt =     false;
    kbd_state.ctrl =    false;
    kbd_state.shift =   false;
    kbd_state.special = false;
    kbd_state.pause =   false;

    //irq_installHandler(33, kbd_irqHandler);

    kbd_setLeds(        false, 
                        false, 
                        false
    );
    
    kdriver_statusMsg_status(KDRIVERS_OK);
    return 0;
}

enum kbd_scancodes {
    // Scancodes can be override if __E_KBD_OVERRIDE_SCANCODES
    // is set by compiler.
    #ifndef __E_KBD_OVERRIDE_SCANCODES

            // Online ref.: https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
            // Online ref.: https://wiki.osdev.org/PS2_Keyboard

        K_UNKNOWN = 0x00,
        K_ESCAPE = 0x01,

        K_1, 
        K_2, 
        K_3, 
        K_4, 
        K_5, 
        K_6, 
        K_7, 
        K_8, 
        K_9, 
        K_0,

        K_DASH,
        K_EQUAL,

        K_TAB,

        K_Q,
        K_W, 
        K_E, 
        K_R, 
        K_T,
        
        #ifndef __E_KBD_QWERTZ
            K_Y,
        #else
            K_Z,
        #endif

        K_U, 
        K_I, 
        K_O, 
        K_P,

        K_SQBRACKETS_OPEN, 
        K_SQBRACKETS_CLOSE,

        K_ENTER,
        K_LCTRL,

        K_A, 
        K_S, 
        K_D, 
        K_F, 
        K_G, 
        K_H, 
        K_J, 
        K_K, 
        K_L,

        K_SEMICOLON, 
        K_COLON, 
        K_SINGLE_QUOTE, 

        K_BACK_TICK,
        K_LSHIFT, 
        K_BACKSLASH,

        #ifndef __E_KBD_QWERTZ
            K_Z,
        #else
            K_Y,
        #endif

        K_X, 
        K_C, 
        K_V, 
        K_B, 
        K_N, 
        K_M,

        K_LESS, 
        K_GREATER, 
        K_SLASH,
        K_RSHIFT, 

        K_ASTERISK,

        K_LALT,
        K_SPACE,
        K_CAPSLOCK,

        K_F1, 
        K_F2, 
        K_F3, 
        K_F4, 
        K_F5, 
        K_F6, 
        K_F7, 
        K_F8, 
        K_F9, 
        K_F10,

        K_NUMLOCK, 
        K_SCROLLLOCK,

        //#ifndef __E_KBD_NO_KEYPAD
            K_KEYPAD_7,
            K_KEYPAD_8,
            K_KEYPAD_9,

            K_KEYPAD_DASH,
            
            K_KEYPAD_4,
            K_KEYPAD_5,
            K_KEYPAD_6,

            K_KEYPAD_PLUS,

            K_KEYPAD_1,
            K_KEYPAD_2,
            K_KEYPAD_3,

            K_KEYPAD_0,
            K_KEYPAD_DOT,
        //#endif

        K_ALT,
        K_FN,
        K_SPECIAL,

        K_F11,
        K_F12
    #endif
};