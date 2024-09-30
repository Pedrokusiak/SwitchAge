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
    
    }


void Player::render(RendererPort* renderer, const Camera& camera) const {
    Vector2D screenPos = camera.worldToScreen(position);
    renderer->drawPlayer(screenPos.x, screenPos.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
