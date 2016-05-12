#ifndef ZERO_ANIMATEDSPRITE_H
#define ZERO_ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include "types.h"

struct AnimatedSprite {
  SDL_Texture* texture;
  vector<SDL_Rect> clip;
  vector<SDL_Point> center;
  vector<u32> interval;
};

AnimatedSprite createAnimatedSprite(const char* texturePath);
void destroyAnimatedSprite(AnimatedSprite* animsprite);

void renderAnimatedSprite(const Sprite* sprite, SDL_Point position);

#endif
