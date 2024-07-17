#include "Player.h"

const float PLAYER_ACC = 10000.0f;
const float PLAYER_JUMP_FORCE = 150000.0f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass)
    : ObjectGame(pos, size, gravity, mass), onGround(false) {}

void Player::handleEvent(EventPort* event) {
    if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT: physicsComponent.applyForce(Vector2D(-PLAYER_ACC, 0)); break;
            case SDLK_RIGHT: physicsComponent.applyForce(Vector2D(PLAYER_ACC, 0)); break;
            case SDLK_UP:
                if (onGround) {
                    physicsComponent.applyForce(Vector2D(0, -PLAYER_JUMP_FORCE));
                    onGround = false;
                }
                break;
        }
    }
}


void Player::render(RendererPort* renderer) const {
    renderer->drawPlayer(position.x, position.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
