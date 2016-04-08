#ifndef ZERO_GLOBALS_H
#define ZERO_GLOBALS_H

#include "types.h"
#include "timer.h"

extern Timer g_timer;

u32 getDeltaTicks();
double getDeltaTime();

#endif
