#include "../drivers/vga/vga.h"
#include "tty/tty.h"
#include "kernel.h"


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str) {
	size_t l = 0;
	while (str[l]) l++;

	return l;
}

void kernel_outputModuleLoadMessage(int status, const char* messageStart, const char* messageEnd, const char* moduleName) {
	print("\n");

	if (status == 0) {
		tty_setColor(10); // light green
		print("OK     : ");
	} else {
		tty_setColor(4); // red
		print("FAILED : ");
	}

	tty_setColor(7);
	print(messageStart);
	print(" ");

	tty_setColor(15);
	print(moduleName);
	print(" ");

	tty_setColor(7);
	print(messageEnd);
}

void* memcpy(void* dest, const void* src, size_t n) {
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (const uint8_t*)src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void* memset(void* s, int c, size_t n) {
    uint8_t* p = (uint8_t*)s;

    for (size_t i = 0; i < n; i++) {
        p[i] = (uint8_t)c;
    }

    return s;
}

void* memmove(void* dest, const void* src, size_t n) {
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (const uint8_t*)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    }
    else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const uint8_t* p1 = (const uint8_t*)s1;
    const uint8_t* p2 = (const uint8_t*)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}