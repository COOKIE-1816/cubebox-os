#include "kmsg.h"
#include "terminal.h"
//#include "vga.h"

const char* kmsg_str[6] = {
	"WARN",
	"ERROR",
	"***",
	"INFO",
	"NOTE",
	"FATAL"
};

static u8 kmsg_colors[6] = {
	0X06,	// Brown
	0X04, // Red
	0b00000110, // Default
	0b00000110, // Default
	0b00000110, // Default 
	0b10001100, // Blinking light red
};

/*String kmsgGen(int __level, String __source, String __message) {
	
}*/

void kmsg(int __level, String __source, String __message) {
	terminal_setColor(kmsg_colors[__level]);
	terminal_wstring(kmsg_str[__level]);
	//terminal_wstring("\t");
	
	terminal_resetColor();
	terminal_wstring("[");
	terminal_wstring(__source);
	terminal_wstring("] ");
	
	terminal_wstring(__message);
	terminal_wstring("\n");
}
