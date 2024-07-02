#include "domain/Player.h"

const int PLAYER_VEL = 5;

Player::Player(int x, int y, int width, int height)
    : posX(x), posY(y), width(width), height(height), velX(0), velY(0), onGround(false) {}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: velX -= PLAYER_VEL; break;
            case SDLK_RIGHT: velX += PLAYER_VEL; break;
            case SDLK_UP:
                if (onGround) {
                    velY = JUMP_FORCE;
                    onGround = false;
                }
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: velX += PLAYER_VEL; break;
            case SDLK_RIGHT: velX -= PLAYER_VEL; break;
        }
    }
}

void Player::move() {
    posX += velX;
    if (posX < 0 || posX + width > 800) {
        posX -= velX;
    }
    velY += GRAVITY;
    if (velY > MAX_FALL_SPEED) {
        velY = MAX_FALL_SPEED;
    }
    posY += velY;
    if (posY + height > 600) {
        posY = 600 - height;
        velY = 0;
        onGround = true;
    } else {
        onGround = false;
    }
}

void Player::render(RendererPort* renderer) {
     renderer->drawPlayer(posX, posY, width, height, 0xFF, 0x00, 0x00, 0xFF);
}
