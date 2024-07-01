#ifndef GAME_H
#define GAME_H
#include <memory>
#include "ports/RendererPort.h"

class Game {
public:
    Game(RendererPort* renderer);
    void run();

private:
    RendererPort* renderer;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
};

#endif