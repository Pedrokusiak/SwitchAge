#include "PlayerPhysics.h"

PlayerPhysics::PlayerPhysics(int gravity, int maxFallSpeed, int jumpForce)
    : gravity(gravity), maxFallSpeed(maxFallSpeed), jumpForce(jumpForce) {}

void PlayerPhysics::applyPhysics(Position& position, int& velX, int& velY, bool& onGround, int width, int height) {
    // Atualiza a posição horizontal
    position.setPositionX(position.getPositionX() + velX);

    // Checa os limites da tela para a posição horizontal
    if (position.getPositionX() < 0 || position.getPositionX() + width > 800) {
        position.setPositionX(position.getPositionX() - velX);
    }

    // Aplica gravidade
    velY += gravity;
    if (velY > maxFallSpeed) {
        velY = maxFallSpeed;
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
