#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "ports/RendererPort.h"
#include "PlayerPhysics.h"
#include <vector>
#include <adapters/SDL/SDLEventAdapter.h>

class Game {
public:
    Game(RendererPort *renderer);
    void run();

private:
    RendererPort *renderer;
    Player player;
    std::vector<GroundSegment> groundSegments;
    PlayerPhysics playerPhysics;
    SDLEventAdapter eventAdapter; 
};

#endif // GAME_HPP
