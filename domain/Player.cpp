#include "Player.h"

const float PLAYER_ACC = 0.5f;
const float PLAYER_FRICTION = 0.1f;
const float PLAYER_JUMP_FORCE = 15.0f;

Player::Player(Vector2D pos, Vector2D size, Physics* physicsComponent)
    : ObjectGame(pos, size, physicsComponent), velocity(0, 0), onGround(false) {}

void Player::handleEvent(EventPort* event) {
    if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT: velocity.x -= PLAYER_ACC; break;
            case SDLK_RIGHT: velocity.x += PLAYER_ACC; break;
            case SDLK_UP:
                if (onGround) {
                    velocity.y = -PLAYER_JUMP_FORCE;
                    onGround = false;
                }
                break;
        }
    }
}

void Player::render(RendererPort* renderer) const {
    renderer->drawPlayer(position.x, position.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
