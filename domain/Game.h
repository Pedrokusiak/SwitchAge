#ifndef GAME_HPP
#define GAME_HPP

#include "Player.h"
#include "GroundSegment.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "Physics.h"
#include <vector>
#include <memory>
#include "ObjectGame.h"

class Game {
public:
    Game(RendererPort *renderer, EventPort *eventPort);
    void run();

private:
    RendererPort *renderer;
    EventPort *eventPort;
    Player player;
    std::vector<std::unique_ptr<ObjectGame>> gameObjects;
    Physics playerPhysics;
    Physics groundPhysics;
};

#endif // GAME_HPP
