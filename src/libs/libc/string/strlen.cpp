#include "libs/libc/string.h"

size_t strlen(String __str) {
    size_t len = 0;

	while (__str[len])
		len++;

	return len;
}