#include <stdint.h>
#include "stdio/stdio.h"

// TODO: initialize with random value in bootloader
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void _noreturn __stack_chk_fail(void);