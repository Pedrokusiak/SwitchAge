#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Position.h"

class Physics {
public:
    virtual ~Physics() = default;
    virtual void applyPhysics(Position& position, int& velX, int& velY, bool& onGround, int width, int height) = 0;
};

#endif // PHYSICSCOMPONENT_HPP
