#include <SDL2/SDL.h>
#include "timer.h"

void startTimer(Timer* timer) {
  u32 t = SDL_GetTicks();
  timer->currentTime = t;
  timer->previousTime = t;
  timer->lastTickUpdate = t;
  timer->isPaused = false;
}

void updateTimer(Timer* timer) {
  if (timer->isPaused) return;

  timer->previousTime = timer->currentTime;

  u32 t = SDL_GetTicks();
  timer->currentTime += t - timer->lastTickUpdate;
  timer->lastTickUpdate = t;
}

void pauseTimer(Timer* timer) {
  timer->isPaused = true;
}

void unpauseTimer(Timer* timer) {
  timer->isPaused = false;
  timer->lastTickUpdate = SDL_GetTicks();
}

double getDeltaTime(const Timer timer) {
  u32 delta = timer.currentTime - timer.previousTime;
  return delta / 1000.0;
}
