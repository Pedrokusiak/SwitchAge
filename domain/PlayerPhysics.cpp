#include "PlayerPhysics.h"
#include "GroundSegment.h"

PlayerPhysics::PlayerPhysics(float gravity, float maxFallSpeed, float jumpForce)
    : gravity(gravity), maxFallSpeed(maxFallSpeed), jumpForce(jumpForce) {}