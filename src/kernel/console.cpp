#include "kernel/console.h"
#include "kernel/cursor.h"
#include "kernel/error.h"
#include "kernel/tty.h"
#include "drivers/vga.h"

using namespace Kernel::TTY;
using namespace Kernel::Cursor;
using namespace Kernel::Console;

String _console_prefix = "> ";
String* _console_buffer;

bool _console_hasHint = true;
bool _console_hint_visible = false;
String _console_hintText = "Type command here. Use '?' or F1 key for general help.";

bool _console_status = 0;

uint8_t _console_lastKey = 0x00;

void showHint() {
    if(_console_hasHint)
        colored(8 /*GRAYED*/, _console_hintText);
}

String getInput() {
    // Draw prefix
    writeString("\n");
    colored(7, _console_prefix);

    showHint();

    cursor_enable();
    cursor_update(2, getRow());

    while(_console_lastKey != 0x1B /*ENTER 27*/) {
        _console_lastKey = 0x00;

        if(_console_hint_visible) {
            // Hide the hint
            for(int i = 2; i < VGA_WIDTH; i++) {
                putEntryAt(' ', 7, i, getRow());
            }
        }
    }
}

void Kernel::Console::leave() {
    writeString("Leaving console...\n");

    _console_status = 1;
    cursor_disable();
}

void Kernel::Console::enter() {
    writeString("Entering command line interface (AKA console)...\n");

    if(commandBuffer > 80) {
        error("CONSOLE_ERR_BUFFER_LARGE");
        return;
    }

    cursor_disable();

    while(_console_status == 0) {

    }
}

void Kernel::Console::setHint(bool __enable, String __hint) {
    _console_hasHint = __enable;

    if(!__enable)
        return;

    if(strlen(__hint) > 80) {
        _console_hasHint = false;
        error("CONSOLE_ERR_HINT_LARGE");
    }
}