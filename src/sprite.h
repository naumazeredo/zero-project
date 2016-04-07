#ifndef ZERO_SPRITE_H
#define ZERO_SPRITE_H

#include <SDL2/SDL.h>

struct Sprite {
  SDL_Texture* texture;
  SDL_Rect clip;
  SDL_Point center;
};

Sprite createSprite(const char* texturePath, SDL_Rect clip, SDL_Point center);
void destroySprite(Sprite* sprite);

void renderSprite(const Sprite* sprite, SDL_Point position);

#endif
