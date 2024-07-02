#include "domain/Player.h"

const int PLAYER_VEL = 5;

Player::Player(Position pos, int width, int height)
    : position(pos), velX(0), velY(0), width(width), height(height), onGround(false) {}

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
    // Atualiza a posição horizontal
    position.setPositionX(position.getPositionX() + velX);

    // Checa os limites da tela para a posição horizontal
    if (position.getPositionX() < 0 || position.getPositionX() + width > 800) {
        position.setPositionX(position.getPositionX() - velX);
    }

    // Aplica gravidade
    velY += GRAVITY;
    if (velY > MAX_FALL_SPEED) {
        velY = MAX_FALL_SPEED;
    }

    // Atualiza a posição vertical
    position.setPositionY(position.getPositionY() + velY);

    // Checa os limites da tela para a posição vertical
    if (position.getPositionY() + height > 600) {
        position.setPositionY(600 - height);
        velY = 0;
        onGround = true;
    } else {
        onGround = false;
    }
}


void Player::render(RendererPort* renderer) {
     renderer->drawPlayer(position.getPositionX(), position.getPositionY(), width, height, 0xFF, 0x00, 0x00, 0xFF);
}
