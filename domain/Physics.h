#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include "Vector2D.h"
#include "GroundSegment.h"
#include <vector>

class Physics {
public:
    virtual ~Physics() = default;
    virtual void applyPhysics(Vector2D& position, Vector2D& velocity, bool& onGround, const Vector2D& size, const std::vector<GroundSegment>& groundSegments) = 0;
};

#endif // PHYSICSCOMPONENT_HPP
