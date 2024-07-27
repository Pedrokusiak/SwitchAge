#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "ports/PlayerRenderPort.h"
#include "ports/PageRenderPort.h"
#include <vector>
#include <memory>

class Game {
public:
    Game(RendererPort *renderer,EventPort *eventPort,PageRenderPort *pageRenderPort);
    void run();

private:
    RendererPort *renderer;
    EventPort *eventPort;
    PageRenderPort *pageRenderPort;
    std::vector<std::unique_ptr<ObjectGame>> gameObjects;
};

#endif // GAME_H
