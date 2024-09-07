#include "Animation.h"
#include <iostream>

Animation::Animation(const std::vector<Frame>& frm, Uint32 interval)
    : frames(frm), currentFrame(0), lastUpdate(0), updateInterval(interval) {}

void Animation::update(Uint32 currentTime) {
    if (currentTime - lastUpdate > updateInterval) {
        currentFrame = (currentFrame + 1) % frames.size();
        lastUpdate = currentTime;
        std::cout << "Animation frame updated to: " << currentFrame << std::endl;
    }
}

Frame Animation::getCurrentFrame() const {
    return frames[currentFrame];
}
