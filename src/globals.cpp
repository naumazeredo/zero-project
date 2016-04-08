#include "globals.h"

u32 getDeltaTicks() {
  return getTimerDeltaTicks(g_timer);
}

double getDeltaTime() {
  return getTimerDeltaTime(g_timer);
}
