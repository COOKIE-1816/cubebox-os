#include "kmsg.h"
#include "terminal.h"
//#include "vga.h"

const char* kmsg_str[6] {
	"WARN",
	"ERROR",
	"***",
	"INFO",
	"NOTE",
	"FATAL"
};

static u8 kmsg_colors[6] {
	0b00000101,	// Brown
	0b00001000, // Red
	0b00000110, // Default
	0b00000110, // Default
	0b00000110, // Default 
	0b10001100, // Blinking light red
};

/*String kmsgGen(int __level, String __source, String __message) {
	
}*/

void kmsg(int __level, String __source, String __message) {
	Terminal::setColor(kmsg_colors[__level]);
	Terminal::wstring(kmsg_str[__level]);
	Terminal::wstring("\t");
	
	Terminal::resetColor();
	Terminal::wstring("[");
	Terminal::wstring(__source);
	Terminal::wstring("] ");
	
	Terminal::wstring(__message);
	Terminal::wstring("\n");
}
