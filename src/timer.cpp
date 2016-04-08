#include <SDL2/SDL.h>
#include "timer.h"

void startTimer(Timer* timer) {
  u32 t = SDL_GetTicks();
  timer->currentTime = t;
  timer->previousTime = t;
  timer->lastTickUpdate = t;
  timer->isPaused = false;
}

static void update(Timer* timer) {
  u32 t = SDL_GetTicks();
  timer->currentTime += t - timer->lastTickUpdate;
  timer->lastTickUpdate = t;
}

void updateTimer(Timer* timer) {
  if (timer->isPaused) return;
  timer->previousTime = timer->currentTime;
  update(timer);
}

void inframeUpdateTimer(Timer* timer) {
  if (timer->isPaused) return;
  update(timer);
}

void pauseTimer(Timer* timer) {
  timer->isPaused = true;
}

void unpauseTimer(Timer* timer) {
  timer->isPaused = false;
  timer->lastTickUpdate = SDL_GetTicks();
}

u32 getTimerDeltaTicks(const Timer timer) {
  return timer.currentTime - timer.previousTime;
}

double getTimerDeltaTime(const Timer timer) {
  u32 delta = timer.currentTime - timer.previousTime;
  return delta / 1000.0;
}
