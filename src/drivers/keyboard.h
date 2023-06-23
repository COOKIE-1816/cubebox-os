#ifndef _CB_KBD_H_
#define _CB_KBD_H_

#include <cboolean.h>
#include <stdint.h>

void kbd_setLeds(   bool __n, // NumLock LED
                    bool __c, // CapsLock LED
                    bool __s  // ScrollLock LED
                );

bool kbd_return_isKeypress(uint8_t __return);

bool* kbd_getLockKeys();
bool kbd_getShift();
bool kbd_getAlt();
bool kbd_getCtrl();
bool kbd_getSpecial();
bool kbd_getPause();

#define KBD_SELF_TEST_OK    true
#define KBD_SELF_TEST_FAIL  false

bool kbd_selfTest();

#define KBD_INTERFACE_TEST_OK                   0x00
#define KBD_INTERFACE_TEST_ERR_CLL_STUCK_LOW    0x01
#define KBD_INTERFACE_TEST_ERR_CLL_STUCK_HIGH   0x02
#define KBD_INTERFACE_TEST_ERR_DATAL_STUCK_HIGH 0x03
#define KBD_INTERFACE_TEST_ERR_GENERAL          0xFF

uint8_t kbd_interfaceTest();


void kbd_setEnabled(bool __enable);
uint8_t kbd_getLast();

int kbd_init();

#endif