#ifndef _CB_ACPI_H_
#define _CB_ACPI_H_

#include "drivers/acpi.h"
#include "drivers/rtc.h"
#include "stringt.h"
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

static dword *SMI_CMD;
static byte ACPI_ENABLE;
static byte ACPI_DISABLE;
static dword *PM1a_CNT;
static dword *PM1b_CNT;
static word SLP_TYPa;
static word SLP_TYPb;
static word SLP_EN;

static byte PM1_CNT_LEN;

static word SCI_EN;

int acpi_enable(void);
int acpi_init(void);

#endif