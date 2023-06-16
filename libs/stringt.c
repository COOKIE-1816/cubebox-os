#include "stringt.h"

inline size_t strlen(String str) {
	size_t len = 0;

	while (str[len])
		len++;

	return len;
}