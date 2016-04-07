#include <cstdio>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "SDL could not be initialized: %s\n",
      SDL_GetError()
    );
    return 1;
  }

  window = SDL_CreateWindow(
    "Zero project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT,
    0
  );

  renderer = SDL_CreateRenderer(window, -1, 0);

  bool isRunning = true;
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
          isRunning = false;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_Quit();

  return 0;
}
