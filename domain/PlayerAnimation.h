#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include "Animation.h"

class PlayerAnimation : public Animation {
public:


    PlayerAnimation(const std::vector<Frame>& frames, Uint32 interval);

    void setDirection(Direction dir);

private:
    Direction currentDirection;
};

#endif // PLAYERANIMATION_H
