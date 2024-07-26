#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "ports/PlayerRenderPort.h"
#include <vector>
#include <memory>

class Game {
public:
    Game(RendererPort *renderer,EventPort *eventPort);
    void run();

private:
    RendererPort *renderer;
    EventPort *eventPort;
    std::vector<std::unique_ptr<ObjectGame>> gameObjects;
};

#endif // GAME_H
