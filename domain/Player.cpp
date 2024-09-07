#include "Player.h"
#include <iostream>

const float PLAYER_FORCE = 1000.0f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate, ITexture* texture, Animation animation )
    : ObjectGame(pos, size, gravity, mass, hibernate, texture, animation ) {}

void Player::handleEvent(EventPort* event) {
    if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT: 
                physicsComponent.applyForce(Vector2D(-PLAYER_FORCE, 0));
                break;
            case SDLK_RIGHT: 
                physicsComponent.applyForce(Vector2D(PLAYER_FORCE, 0));
                break;
            case SDLK_UP:
                physicsComponent.applyForce(Vector2D(0, -PLAYER_FORCE));
                break;
            case SDLK_DOWN:
                physicsComponent.applyForce(Vector2D(0, PLAYER_FORCE));
                break;

            default:
                 physicsComponent.applyForce(Vector2D(0, 0));
                 break;
        }
    }
}


void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    ObjectGame::update(deltaTime, gameObjects);
    animation.update(deltaTime);
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            if (position.y + size.y <= object->getPosition().y) {
                position.y = object.get()->getPosition().y - size.y;
                physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0));
            }
        }
    }
}


void Player::render(RendererPort* renderer) const {
    Frame currentFrame = animation.getCurrentFrame(); 
    renderer->drawTexture(texture, position.x, position.y, currentFrame.width, currentFrame.height);
}
