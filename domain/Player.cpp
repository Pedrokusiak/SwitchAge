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


void Player::render(RendererPort* renderer) const {
    std::cout << "Player position: (" << position.x << ", " << position.y << ")" << std::endl;

    if (animation) {
        animation->render(position.x, position.y);
    } else {
        renderer->drawRect(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            255, 0, 0, 255  // Vermelho sólido
        );
    }

    // Opcional: Renderizar informações de debug
    #ifdef DEBUG_RENDER
        // Renderiza a hitbox
        renderer->drawRect(
            static_cast<int>(hitbox.getPosition().x),
            static_cast<int>(hitbox.getPosition().y),
            static_cast<int>(hitbox.getSize().x),
            static_cast<int>(hitbox.getSize().y),
            0, 255, 0, 128  // Verde semi-transparente
        );

        // Renderiza o vetor de velocidade
        Vector2D velocityEnd = position + physicsComponent.getVelocity() * 10.0f;
        renderer->drawLine(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(velocityEnd.x),
            static_cast<int>(velocityEnd.y),
            0, 0, 255, 255  // Azul
        );
    #endif
}

void Player::addAnimation(const std::string& name, const std::vector<int>& frameIndices) {
    animation->addAnimation(name, frameIndices);
}

void Player::playAnimation(const std::string& name, bool loop) {
    animation->playAnimation(name, loop);
}