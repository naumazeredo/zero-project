#ifndef ZERO_SPRITE_H
#define ZERO_SPRITE_H

#include "includes.h"
#include "types.h"

struct Sprite {
  Texture* texture;
  Rect clip;
  Point center;
};

Sprite createSprite(const char* texturePath, Rect clip, Point center);
void destroySprite(Sprite* sprite);

void renderSprite(const Sprite& sprite, Point position);

#endif
