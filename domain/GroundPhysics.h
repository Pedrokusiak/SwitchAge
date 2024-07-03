#ifndef GROUNDPHYSICS_HPP
#define GROUNDPHYSICS_HPP

#include "Physics.h"

class GroundPhysics : public Physics {
public:
    void applyPhysics(Position& position, int& velX, int& velY, bool& onGround, int width, int height) override;
};

#endif // GROUNDPHYSICS_HPP
