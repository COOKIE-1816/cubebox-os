#include "text_ui/boxes.h"
#include "text_ui/shapes.h"
#include "drivers/vga.h"

tty_img _ttyImage;

/*void _createShadow(Box __box) {

}*/

uint8_t _ec;

void _createTitle(Box __box) {
    size_t l = strlen(__box.title);

    
}

void createBox(Box __box) {
    for(size_t hi = 0; hi < __box.height; hi++)
        drawLineH(__box.x, __box.x + __box.width, __box.y + hi, __box.background);
}