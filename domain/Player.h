#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "ports/RendererPort.h"
class Player {
public:
    Player(int x, int y, int width, int height);
    void handleEvent(SDL_Event& e);
    void move();
    void render(RendererPort* renderer);

private:
    int posX, posY;
    int velX, velY;
    int width, height;
    bool onGround;

    const int GRAVITY = 1;
    const int MAX_FALL_SPEED = 10;
    const int JUMP_FORCE = -15;
};

#endif // PLAYER_H
