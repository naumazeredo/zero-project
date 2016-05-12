#include "globals.h"
#include "rigidbody.h"

void updateRigidbody(Rigidbody* rb) {
  rb->position += rb->velocity * getDeltaTime();
}
