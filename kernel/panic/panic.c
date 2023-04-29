#include "panic.h"
#include "../tty/tty.h"

void kpanic(const char* reason) {
	println("--- kernel panic ---");
}