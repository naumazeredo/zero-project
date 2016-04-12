#include "globals.h"
#include "physicsobject.h"

void updatePhysicsObject(PhysicsObject* obj) {
  obj->position += obj->velocity * getDeltaTime();
}
