#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"
#include "types.h"
#include "timer.h"
#include "sprite.h"
#include "texture.h"

// TODO(naum): Refactor
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool isRunning;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;

char title[32];

Timer g_timer;
u32 frameCount;
u32 frameTimeLast;
double frameTime;

// Test
i32 x = 100, y = 100;
// ----

bool startGame();
void quitGame();
void startWindow();
void destroyWindow();

void handleInput();

int main() {
  startGame();

  // Test
  Sprite sprite = createSprite("assets/blank.png", {0, 0, 32, 32}, {0, 0});
  // ----

  startTimer(&g_timer);
  u32 previousTime = g_timer.currentTime;

  frameTimeLast = g_timer.currentTime;
  frameTime = 0.0f;

  isRunning = true;
  while (isRunning) {
    handleInput();

    SDL_RenderClear(g_renderer);

    // Render
    renderSprite(&sprite, {x, y});
    // ------

    SDL_RenderPresent(g_renderer);

    // Frames per second
    updateTimer(&g_timer);

    frameCount++;
    double frameTimeAlpha = 0.2;
    frameTime = frameTimeAlpha * getDeltaTime() + (1 - frameTimeAlpha) * frameTime;
    if (g_timer.currentTime - previousTime >= 200) {
      sprintf(title, "Zero Project - %4.2f FPS", 1 / frameTime);
      SDL_SetWindowTitle(g_window, title);
      previousTime = g_timer.currentTime;
    }
  }

  // Test cleanup
  destroySprite(&sprite);
  // ----

  quitGame();

  return 0;
}

// -------------------------------
// TODO(naum): Refactor into another file

bool startGame() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "SDL_Init - SDL could not be initialized: %s\n",
      SDL_GetError()
    );

    return false;
  }

  int img_flags = IMG_INIT_PNG;
  if ((IMG_Init(img_flags) & img_flags) != img_flags) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "IMG_Init - Could not initialize PNG support: %s\n",
      IMG_GetError()
    );

    return false;
  }

  startWindow();

  return true;
}

void quitGame() {
  destroyWindow();
  IMG_Quit();
  SDL_Quit();
}

void startWindow() {
  g_window = SDL_CreateWindow(
    "Zero Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, 0
  );

  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
  //g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void destroyWindow() {
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);

  g_renderer = nullptr;
  g_window = nullptr;
}


void handleInput() {
  // Keystate
  const u8* keyState = SDL_GetKeyboardState(0);

  if (keyState[SDL_SCANCODE_D]) x++;
  if (keyState[SDL_SCANCODE_A]) x--;
  if (keyState[SDL_SCANCODE_S]) y++;
  if (keyState[SDL_SCANCODE_W]) y--;

  // Events
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
      SDL_Keycode sym = event.key.keysym.sym;

      if (sym == SDLK_ESCAPE)
        isRunning = false;
      if (sym == SDLK_j) pauseTimer(&g_timer);
      if (sym == SDLK_k) unpauseTimer(&g_timer);
    }
  }
}
