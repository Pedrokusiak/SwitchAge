#include "Player.h"
#include "ITexture.h"
#include <iostream>
#include "MixerManager.h" // Inclua o MixerManager
#include "Animation.h"
const float PLAYER_FORCE = 1000.0f;
const float PLAYER_MOVEMENT_FORCE = 800.0f;
const float GRAVITY_MAGNITUDE = 1000.0f;
const float GRAVITY_FLIP_COOLDOWN = 0.5f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
               std::shared_ptr<ITexture> texture, RendererPort* renderer, 
               int frameWidth, int frameHeight, GameAudio::MixerManager* mixerManager)
    : ObjectGame(pos, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight), mixerManager(mixerManager) {}

void Player::handleEvent(EventPort* event) {
   if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT:
                animation->playAnimation("walkLeft", true);
                physicsComponent.applyForce(Vector2D(-1000, 0));

                break;
            case SDLK_RIGHT:
                physicsComponent.applyForce(Vector2D(1000, 0));
                physicsComponent.applyForce(Vector2D(1000, 0));
                break;
            case SDLK_UP:
                if (physicsComponent.getVelocity().y == 0) {

                    animation->playAnimation("jumpUp", false);
                    physicsComponent.applyForce(Vector2D(0, -1000));
                    
                    mixerManager->playSound("jump");
                }
                break;
            case SDLK_DOWN:

                animation->playAnimation("crouch", false);
                physicsComponent.applyForce(Vector2D(0, PLAYER_FORCE));
                break;

            default:
                animation->playAnimation("idle", false);
                physicsComponent.applyForce(Vector2D(0, 0));
                break;
        }
    }
}


void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    ObjectGame::update(deltaTime, gameObjects);
    
    bool isGrounded = false;
    for (const auto& object : gameObjects)
    {
        if (this != object.get() && checkCollision(*object))
        {
            isGrounded = true;
            Vector2D normal = calculateCollisionNormal(*object);
            handleGroundedState(normal);
        }
    }
}

Vector2D Player::calculateCollisionNormal(const ObjectGame& other) const
{
    Vector2D centerDiff = other.getPosition() - position;
    Vector2D normal(0, 0);
    
    if (std::abs(centerDiff.y) > std::abs(centerDiff.x))
    {
        normal.y = centerDiff.y > 0 ? 1 : -1;
    }
    else
    {
        normal.x = centerDiff.x > 0 ? 1 : -1;
    }
    
    return normal;
}

void Player::handleGroundedState(const Vector2D& normal)
{
    Vector2D vel = physicsComponent.getVelocity();
    if ((normal.y > 0 && vel.y > 0) || (normal.y < 0 && vel.y < 0))
    {
        vel.y = 0;
        physicsComponent.setVelocity(vel);
    }
}

void Player::render(RendererPort* renderer, const Camera& camera) const
{
    Vector2D screenPos = camera.worldToScreen(position);
    renderer->drawPlayer(screenPos.x, screenPos.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}


void Player::addAnimation(const std::string& name, const std::vector<int>& frameIndices) {
    animation->addAnimation(name, frameIndices);
    std::cout << "Animação " << name << " adicionada com " << frameIndices.size() << " frames." << std::endl;
}

void Player::playAnimation(const std::string& name, bool loop) {
    animation->playAnimation(name, loop);

}