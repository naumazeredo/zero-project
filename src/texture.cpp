#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

extern SDL_Renderer* renderer;

SDL_Texture* loadTexture(const char* path) {
  SDL_Texture* texture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(path);
  if (!loadedSurface) {
    SDL_LogError(
      SDL_LOG_CATEGORY_VIDEO,
      "loadTexture - Could not load image %s: %s\n",
      path, IMG_GetError()
    );

    return nullptr;
  }

  texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if (!texture) {
    SDL_LogError(
      SDL_LOG_CATEGORY_VIDEO,
      "loadTexture - Could not create texture: %s\n",
      SDL_GetError()
    );
  }

  SDL_FreeSurface(loadedSurface);
  return texture;
}
