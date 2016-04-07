#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"
#include "texture.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool isRunning;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

  isRunning = true;
  while (isRunning) {
    handleInput();

    SDL_RenderClear(renderer);

    // Render
    //SDL_RenderCopy(renderer, sprite.texture, &sprite.clip, 0);
    renderSprite(&sprite, {10, 10});
    // ------

    SDL_RenderPresent(renderer);
  }

  // Test cleanup
  destroySprite(&sprite);
  // ----

  quitGame();

  return 0;
}

// -------------------------------

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
    "Zero project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, 0
  );

  renderer = SDL_CreateRenderer(window, -1, 0);
}

void destroyWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  renderer = nullptr;
  window = nullptr;
}


void handleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE)
        isRunning = false;
    }
  }
}
