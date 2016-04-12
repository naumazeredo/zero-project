#ifndef ZERO_PHYSICSOBJECT_H
#define ZERO_PHYSICSOBJECT_H

#include "types.h"

struct PhysicsObject {
  vec2 position;
  vec2 velocity;
};

void updatePhysicsObject(PhysicsObject*);

#endif
