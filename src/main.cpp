#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "sprite.h"
#include "texture.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool isRunning;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
char title[32];

u32 frameCount = 0;
u32 frameTime = SDL_GetTicks();

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

  frameTime = SDL_GetTicks();

  isRunning = true;
  while (isRunning) {
    handleInput();

    SDL_RenderClear(renderer);

    // Render
    renderSprite(&sprite, {x, y});
    // ------

    SDL_RenderPresent(renderer);

    // Frames per second
    frameCount++;
    u32 curTime = SDL_GetTicks();
    if (curTime - frameTime >= 1000) {
      sprintf(title, "Zero Project - %d FPS", frameCount);
      SDL_SetWindowTitle(window, title);
      frameTime += 1000;
      frameCount = 0;
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
  window = SDL_CreateWindow(
    "Zero Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, 0
  );

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void destroyWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  renderer = nullptr;
  window = nullptr;
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
    }
  }
}
