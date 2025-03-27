#include "arch/sys_arch.h"

u32_t sys_now(void) { return HAL_GetTick(); }