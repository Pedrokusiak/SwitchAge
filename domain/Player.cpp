#include "domain/Player.h"
#include "Player.h"
#include "Physics.h"

const int PLAYER_VEL = 5;

Player::Player(Position pos, int width, int height, Physics* physicsComponent)
    : position(pos), width(width), height(height), physicsComponent(physicsComponent), velX(0), velY(0), onGround(false) {}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: velX -= PLAYER_VEL; break;
            case SDLK_RIGHT: velX += PLAYER_VEL; break;
            case SDLK_UP:
                if (onGround) {
                    velY = -15;  // Usando o valor fixo para o salto
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
    physicsComponent->applyPhysics(position, velX, velY, onGround, width, height);
}

void Player::render(RendererPort* renderer) {
    renderer-> drawPlayer(position.getPositionX(), position.getPositionY(), width, height, 0xFF, 0x00, 0x00, 0xFF);
}
