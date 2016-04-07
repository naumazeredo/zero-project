#ifndef ZERO_TIMER_H
#define ZERO_TIMER_H

#include "types.h"

struct Timer {
  u32 currentTime,
      previousTime;
  u32 lastTickUpdate;
  bool isPaused;
};

void startTimer(Timer*);
void updateTimer(Timer*);
void pauseTimer(Timer*);
void unpauseTimer(Timer*);

double getDeltaTime(const Timer);

#endif
