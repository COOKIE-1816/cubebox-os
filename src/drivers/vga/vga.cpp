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
	/*
		The VGA Driver uses 16 bit register (uint16_t aka u16) to express if a char is blinking 
		or not, express background and foreground color, and char itself. 
		
							   +------------------------------ u8 (aka uint8_t) __color
							   |
			+------------------+----------------+		+----- uc (aka unsigned char) __char
			|									|		|
		+-----------+---------------+---------------+-------------------------------+
		| Blinking	|	Background	| 	Foreground	|	Char 						|
		|			|	color		|	color		|								|
		+-----------+----+----+-----+---+---+---+---+---+---+---+---+---+---+---+---+
		|	15		| 14 | 13 | 12  | 11| 10| 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
		+---+-------+----+----+-----+---+---+---+---+---+---+---+---+---+---+---+---+
			|
			+----------------------------------	NOTE - BACKGROUND COLOR LIMITATION:
												As there are 16 colors, these 16 
												colors does not fit in 3-bit value,
												as bit no. 15 is used to toggle 
												blinking on and off.
												
												This will result by making the text 
												blink, if any color equal to or 
												higher than 7 (aka VGA_COLOR_LIGHT_GREY)
												is set as a background color.
												
												TODO: Fix this.
	*/
	
    return (u16) __char | (u16) __color << 8;
}

inline void Vga::init() {
    setPalete(4);
}
