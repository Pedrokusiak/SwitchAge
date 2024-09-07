#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"
#include <SDL2/SDL.h>

class Animation {
private:
    std::vector<Frame> frames;
    int currentFrame;
    Uint32 lastUpdate;
    Uint32 updateInterval;

public:

    enum class Direction {
        Left,
        Right,
        Up,
        Down
    };
    Animation(const std::vector<Frame>& frm, Uint32 interval);

    void update(Uint32 currentTime);

    Frame getCurrentFrame() const;

    void setDirection(Direction dir){
        
    }
};


#endif // GAME_H