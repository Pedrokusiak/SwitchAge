#include "Player.h"
#include <iostream>
#include "MixerManager.h" // Inclua o MixerManager

const float PLAYER_FORCE = 1000.0f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate, ITexture* texture, GameAudio::MixerManager* mixerManager)
    : ObjectGame(pos, size, gravity, mass, hibernate, texture), mixerManager(mixerManager) {}

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
                // Certifique-se de que o jogador está no chão antes de pular
                if (physicsComponent.getVelocity().y == 0) {
                    physicsComponent.applyForce(Vector2D(0, -PLAYER_FORCE));
                    
                    // Reproduzir som de pulo usando o mixerManager
                    mixerManager->playSound("jump");
                }
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
    if (texture) {
        int width = texture->getWidth();
        int height = texture->getHeight();
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);
        renderer->drawTexture(texture, x, y, width, height);
    }
}
