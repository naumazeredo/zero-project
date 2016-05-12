#ifndef ZERO_RIGIDBODY_H
#define ZERO_RIGIDBODY_H

#include "types.h"

struct Rigidbody {
  vec2 position;
  vec2 velocity;

  // TODO(naum): Add mass and force related stuff
};

void updateRigidbody(Rigidbody*);

#endif
