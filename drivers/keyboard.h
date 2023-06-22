#ifndef _CB_KBD_H_
#define _CB_KBD_H_

#include <cboolean.h>

void kbd_setLeds(   bool __n, // NumLock LED
                    bool __c, // CapsLock LED
                    bool __s  // ScrollLock LED
                );

bool kbd_return_isKeypress(uint8_t __return);
 

#endif