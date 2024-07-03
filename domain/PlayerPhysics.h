#ifndef PLAYERPHYSICS_HPP
#define PLAYERPHYSICS_HPP

#include "Physics.h"
#include <SDL2/SDL.h>

class PlayerPhysics : public Physics {
public:
    PlayerPhysics(int gravity, int maxFallSpeed, int jumpForce);
    void applyPhysics(Position& position, int& velX, int& velY, bool& onGround, int width, int height) override;

private:
    int gravity;
    int maxFallSpeed;
    int jumpForce;
};

#endif // PLAYERPHYSICS_HPP
