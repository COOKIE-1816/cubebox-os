#ifndef _CB_TIMING_DT_H_
#define _CB_TIMING_DT_H_

#include <stdint.h>
#include <stringt.h>

typedef struct {
    uint8_t h;
    uint8_t m;
    uint8_t s;
} time;

static String months[12] = {
    "january",
    "february",
    "march",
    "april",
    "may",
    "june",
    "july",
    "august",
    "september",
    "october",
    "november",
    "december"
};

static String months_short[12] = {
    "jan",
    "feb",
    "mar",
    "jun",
    "jul",
    "aug",
    "sep",
    "oct",
    "nov",
    "dec"
};

#endif