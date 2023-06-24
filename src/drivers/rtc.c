#include "drivers/rtc.h"
#include "kernel/common.h"

uint8_t rtc_readRegister(uint8_t reg) {
    outb(RTC_PORT_INDEX, reg);
    return inb(RTC_PORT_DATA);
}

void rtc_getTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
    uint8_t status_b;

    outb(RTC_PORT_INDEX, 0x0B);
    status_b = inb(RTC_PORT_DATA);

    while (status_b & 0x80) {
        outb(RTC_PORT_INDEX, 0x0B);
        status_b = inb(RTC_PORT_DATA);
    }

    *seconds =  rtc_readRegister(RTC_REG_SECONDS);
    *minutes =  rtc_readRegister(RTC_REG_MINUTES);
    *hours =    rtc_readRegister(RTC_REG_HOURS);
}

static time _buff;

time rtc_now() {
    uint8_t h, m, s;

    rtc_getTime(&h, &m, &s);

    _buff.h = h;
    _buff.m = m;
    _buff.s = s;

    return _buff;
}

void rtc_sleep(uint8_t __seconds) {
    if(__seconds >= 60)
        // The timer can not count more than 59 seconds.
        return;

    uint8_t now  = rtc_readRegister(RTC_REG_SECONDS);
    uint8_t wake = now + __seconds;

    while(now != wake)
        now = rtc_readRegister(RTC_REG_SECONDS);
}