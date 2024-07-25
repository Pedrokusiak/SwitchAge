#include "Player.h"

const float PLAYER_ACC = 1000.0f;
const float PLAYER_JUMP_FORCE = -15000.0f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass)
    : ObjectGame(pos, size, gravity, mass), onGround(false) {}

void Player::handleEvent(EventPort* event) {
    if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT: 
                physicsComponent.applyForce(Vector2D(-PLAYER_ACC, 0));
                break;
            case SDLK_RIGHT: 
                physicsComponent.applyForce(Vector2D(PLAYER_ACC, 0));
                break;
            case SDLK_UP:

                    physicsComponent.applyForce(Vector2D(0, PLAYER_JUMP_FORCE));
                    onGround = false;
                    printf("Pular: Não está no chão, não pode pular\n");
                break;
        }
    }
}

void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    ObjectGame::update(deltaTime, gameObjects);
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            if (position.y + size.y <= object->getPosition().y) {
                onGround = true;
                position.y = object.get()->getPosition().y - size.y;
                physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0));
            }
        }
    }
}

void Player::render(RendererPort* renderer) const {
    renderer->drawPlayer(position.x, position.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
