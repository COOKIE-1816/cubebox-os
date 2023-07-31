#include "drivers/vga/vga.h"

inline void Vga::setPalete(int __bits) {
    _pallete = __bits;
}

/*
inline u8 Vga::entryColor1x(enum Vga::color1x __foreground, enum Vga::color1x __background) {
    return __foreground | __background << 4;
}

inline u8 Vga::entryColor2x(enum Vga::color2x __foreground, enum Vga::color2x __background) {
    return __foreground | __background << 4;
}
*/

inline u8 Vga::entryColor(enum Vga::color4x __foreground, enum Vga::color4x __background) {
    return __foreground | __background << 4;
}

inline u16 Vga::entry(uc __char, u8 __color) {
    return (u16) __char | (u16) __color << 8;
}

inline void Vga::init() {
    setPalete(4);
}