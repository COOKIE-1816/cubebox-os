#ifndef _CB_TIMING_DT_H_
#define _CB_TIMING_DT_H_

#include <stdint.h>
#include <stringt.h>

/*
    This kernel library provides:
        * Data types related to date and time
        * Months, etc. names as strings
*/

typedef struct {
    uint8_t h;
    uint8_t m;
    uint8_t s;
} time;

typedef struct {
    uint8_t day;
    uint8_t month;
    uint8_t year;
} date;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;

    uint8_t day;
    uint8_t month;
    uint8_t year;
} datetime;

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