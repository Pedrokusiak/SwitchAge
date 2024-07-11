#ifndef PLAYERPHYSICS_HPP
#define PLAYERPHYSICS_HPP

#include "Physics.h"
#include "Vector2D.h"
#include <vector>

class PlayerPhysics {
public:
    PlayerPhysics(float gravity, float maxFallSpeed, float jumpForce);
    void applyPhysics(Vector2D& position, Vector2D& velocity, bool& onGround, const Vector2D& size, const std::vector<GroundSegment>& groundSegments) override;

private:
    float gravity;
    float maxFallSpeed;
    float jumpForce;
};

#endif // PLAYERPHYSICS_HPP
