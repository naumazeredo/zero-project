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
void inframeUpdateTimer(Timer*);
void pauseTimer(Timer*);
void unpauseTimer(Timer*);

u32 getTimerDeltaTicks(const Timer);
double getTimerDeltaTime(const Timer);

#endif
