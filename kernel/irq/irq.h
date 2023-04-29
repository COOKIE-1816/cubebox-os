#pragma once
#include <stdint.h>

void irq_setMask(unsigned char IRQline);
void irq_clearMask(unsigned char IRQline);