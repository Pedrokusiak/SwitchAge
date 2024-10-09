#include "Player.h"
#include <iostream>
#include <cmath>

const float PLAYER_MOVEMENT_FORCE = 800.0f;
const float GRAVITY_MAGNITUDE = 1000.0f;
const float GRAVITY_FLIP_COOLDOWN = 0.5f;

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate)
    : ObjectGame(pos, size, gravity, mass, hibernate), lastGravityFlip(0.0f)
{
}

void Player::handleEvent(EventPort* event)
{
    const float currentTime = SDL_GetTicks() / 1000.0f;
    
    if (event->isKeyDownEvent())
    {
        switch (event->getKey())
        {
            case SDLK_LEFT:
                physicsComponent.applyForce(Vector2D(-PLAYER_MOVEMENT_FORCE, 0));
                break;
            case SDLK_RIGHT:
                physicsComponent.applyForce(Vector2D(PLAYER_MOVEMENT_FORCE, 0));
                break;
            case SDLK_SPACE:
                if (currentTime - lastGravityFlip >= GRAVITY_FLIP_COOLDOWN)
                {
                    Vector2D currentGravity = physicsComponent.getGravity();
                    Vector2D newGravity = Vector2D(0, currentGravity.y > 0 ? -GRAVITY_MAGNITUDE : GRAVITY_MAGNITUDE);
                    physicsComponent.setGravity(newGravity);
                    lastGravityFlip = currentTime;
                    
                    // Adiciona um pequeno impulso na direção da nova gravidade
                    physicsComponent.applyForce(newGravity * 0.5f);
                }
                break;
        }
    }
}

void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects)
{
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