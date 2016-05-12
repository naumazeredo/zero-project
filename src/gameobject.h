#ifndef ZERO_GAMEOBJECT_H
#define ZERO_GAMEOBJECT_H

#include "types.h"
#include "rigidbody.h"

struct GameObject {
  u32 uid;
  Rigidbody rigidbody;
  Sprite sprite;

  bool isEnabled;
};

#endif
