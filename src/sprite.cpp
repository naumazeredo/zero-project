#include "texture.h"
#include "sprite.h"

extern SDL_Renderer* renderer;

Sprite createSprite(const char* texturePath, SDL_Rect clip, SDL_Point center) {
  return { loadTexture(texturePath), clip, center };
}

void destroySprite(Sprite* sprite) {
  SDL_DestroyTexture(sprite->texture);
}

void renderSprite(const Sprite* sprite, SDL_Point position) {
  SDL_Rect dest {
    position.x - sprite->center.x,
    position.y - sprite->center.y,
    sprite->clip.w,
    sprite->clip.h
  };

  SDL_RenderCopy(renderer, sprite->texture, &sprite->clip, &dest);
}
