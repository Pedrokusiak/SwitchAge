#ifndef PLAYERPHYSICS_HPP
#define PLAYERPHYSICS_HPP

#include "Physics.h"
#include "Vector2D.h"
#include <vector>

class PlayerPhysics {
public:
    PlayerPhysics(float gravity, float maxFallSpeed, float jumpForce);

private:
    float gravity;
    float maxFallSpeed;
    float jumpForce;
};

#endif // PLAYERPHYSICS_HPP
