#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(const std::vector<Frame>& frames, Uint32 interval)
    : Animation(frames, interval), currentDirection(Direction::Right) {}

void PlayerAnimation::setDirection(Direction dir) {
    if (currentDirection != dir) {
        currentDirection = dir;
        if (dir == Direction::Left) {
        } else if (dir == Direction::Right) {
        }
    }
}
