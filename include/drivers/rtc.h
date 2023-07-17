#ifndef _CB_TIMING_RTC_H_
#define _CB_TIMING_RTC_H_

#define RTC_PORT_INDEX 0x70
#define RTC_PORT_DATA 0x71

#define RTC_REG_SECONDS 0x00
#define RTC_REG_MINUTES 0x02
#define RTC_REG_HOURS 0x04
#define RTC_REG_DAY_OF_WEEK 0x06
#define RTC_REG_DAY_OF_MONTH 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09

#include "datetime.h"
#include <stdint.h>

uint8_t rtc_readRegister(uint8_t reg);
void rtc_getTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);
time rc_now();
void rtc_sleep(uint8_t __seconds);

#endif