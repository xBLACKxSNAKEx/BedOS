#pragma once

#include "drivers/VGA/VGA.h"
#include "x86.h"

void putc(char);
void puts(const char *str);
void printf(const char *str, ...);