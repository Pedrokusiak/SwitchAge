#ifndef GAME_H
#define GAME_H
#include <memory>
#include "ports/RendererPort.h"
#include "Player.h"
#include "PlayerPhysics.h" 

class Game {
public:
    Game(RendererPort* renderer);
    void run();

private:
    RendererPort* renderer;
    Player player;
    PlayerPhysics playerPhysics;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
};

#endif