#include "kernel/timing/rtc.h"
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

time rtc_now() {
    uint8_t h, m, s;
    time buff;

    rtc_getTime(&h, &m, &s);

    buff.h = h;
    buff.m = m;
    buff.s = s;
}

void rtc_sleep(uint8_t __seconds) {
    uint8_t c;
    c = rtc_readRegister(RTC_REG_SECONDS);

    while(c != (c + __seconds) % 60)
        c = rtc_readRegister(RTC_REG_SECONDS);
}