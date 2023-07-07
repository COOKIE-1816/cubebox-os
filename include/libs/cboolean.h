#ifndef _CB_BOOLEAN_H_
#define _CB_BOOLEAN_H_

// Boolean is defined by default in C++.
// This is why this is here, so booleans will not be redefined.
#ifndef __cplusplus
typedef unsigned int bool;

extern bool true = 1;
extern bool false = 0;
#endif

#endif