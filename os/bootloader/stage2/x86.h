#pragma once
#include "stdint.h"

void _cdecl x86_div_64_32(uint64_t divident, uint32_t divisor, uint64_t* quotientOut, uint32_t* reminderOut);

void _cdecl x86_Video_WriteChar(char c, uint8_t page);
