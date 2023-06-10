#pragma once

#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

typedef const char* String;

extern size_t strlen(String str) {
	size_t len = 0;

	while (str[len])
		len++;

	return len;
}

#endif