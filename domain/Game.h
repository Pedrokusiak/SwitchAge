#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "PlayerPhysics.h"
#include <vector>
#include <adapters/SDL/SDLEventAdapter.h>

class Game {
public:
    Game(RendererPort *renderer, EventPort *eventPort);
    void run();

private:
    RendererPort *renderer;
    EventPort *eventPort;
    Player player;
    std::vector<GroundSegment> groundSegments;
    PlayerPhysics playerPhysics;  
};

#endif // GAME_HPP
