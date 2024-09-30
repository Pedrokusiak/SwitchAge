#include "Player.h"
#include "ITexture.h"
#include <iostream>
#include "Animation.h"
const float PLAYER_FORCE = 1000.0f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
           std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight)
    : ObjectGame(pos, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight) {
    }

void Player::handleEvent(EventPort* event) {
   if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT:
                physicsComponent.applyForce(Vector2D(-100, 0));
                animation->playAnimation("walkLeft", true);
                break;
            case SDLK_RIGHT:
                physicsComponent.applyForce(Vector2D(100, 0));
                animation->playAnimation("walkRight", true);
                break;
            case SDLK_UP:
                physicsComponent.applyForce(Vector2D(0, -100));
                animation->playAnimation("jumpUp", false);
                break;
            case SDLK_DOWN:
                physicsComponent.applyForce(Vector2D(0, 100));
                animation->playAnimation("crouch", true);
                break;
        }
    }
}


void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    ObjectGame::update(deltaTime, gameObjects);
    animation->update(deltaTime);
    
    }


void Player::render(RendererPort* renderer, const Camera& camera) const {
    Vector2D screenPos = camera.worldToScreen(position);
    
    int screenX = static_cast<int>(screenPos.x);
    int screenY = static_cast<int>(screenPos.y);

    animation->render(screenX, screenY);
}

void Player::addAnimation(const std::string& name, const std::vector<int>& frameIndices) {
    animation->addAnimation(name, frameIndices);
}

void Player::playAnimation(const std::string& name, bool loop) {
    animation->playAnimation(name, loop);
}