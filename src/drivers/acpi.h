#ifndef _CB_ACPI_H_
#define _CB_ACPI_H_

#include "drivers/acpi.h"
#include "drivers/rtc.h"
#include "stringt.h"
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

/*extern  dword *SMI_CMD;
extern  byte ACPI_ENABLE;
extern  byte ACPI_DISABLE;
extern  dword *PM1a_CNT;
extern  dword *PM1b_CNT;
extern  word SLP_TYPa;
extern  word SLP_TYPb;
extern  word SLP_EN;
extern byte PM1_CNT_LEN;
extern word SCI_EN;*/


int acpi_enable(void);
int acpi_init(void);

int acpi_shutdown(void) ;// Performs a shut-down using ACPI


dword* get_SMI_CMD();
byte get_ACPI_ENABLE();
byte get_ACPI_DISABLE();
dword* get_PM1a_CNT();
dword* get_PM1b_CNT();
word get_SLP_TYPa();
word get_SLP_TYPb();
word get_SLP_EN();
byte get_PM1_CNT_LEN();
word get_SCI_EN();

#endif