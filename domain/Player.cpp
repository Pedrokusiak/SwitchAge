#include "Player.h"
#include "ITexture.h"
#include <iostream>
#include "MixerManager.h" // Inclua o MixerManager
#include "Animation.h"

Player::Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate,
               std::shared_ptr<ITexture> texture, RendererPort *renderer,
               int frameWidth, int frameHeight, GameAudio::MixerManager *mixerManager)
    : ObjectGame(pos, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight), mixerManager(mixerManager)
{
}

void Player::handleEvent(EventPort* event)
{
    const float PLAYER_MOVEMENT_FORCE = 800.0f;

    if (event->isKeyDownEvent())
    {
        switch (event->getKey())
        {
        case SDLK_LEFT:
            if (!animation->isPlayingAnimation("walkLeft"))
            {
                animation->playAnimation("walkLeft", true);
            }
            physicsComponent.applyForce(Vector2D(-PLAYER_MOVEMENT_FORCE, 0));
            break;
        case SDLK_RIGHT:
            if (!animation->isPlayingAnimation("walkRight"))
            {
                animation->playAnimation("walkRight", true);
            }
            physicsComponent.applyForce(Vector2D(PLAYER_MOVEMENT_FORCE, 0));
            break;
        case SDLK_SPACE:
            flipGravity();
            break;
        }
    }
    else if (event->isKeyUpEvent())
    {
        switch (event->getKey())
        {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            if (!animation->isPlayingAnimation("idle"))
            {
                animation->playAnimation("idle", true);
            }
            break;
        }
    }
}


void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>> &gameObjects)
{
    ObjectGame::update(deltaTime, gameObjects);

    bool isGrounded = false;
    for (const auto &object : gameObjects)
    {
        if (this != object.get() && checkCollision(*object))
        {
            isGrounded = true;
            Vector2D normal = calculateCollisionNormal(*object);
            handleGroundedState(normal);
        }
    }
}

Vector2D Player::calculateCollisionNormal(const ObjectGame &other) const
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

void Player::handleGroundedState(const Vector2D &normal)
{
    Vector2D vel = physicsComponent.getVelocity();
    if ((normal.y > 0 && vel.y > 0) || (normal.y < 0 && vel.y < 0))
    {
        vel.y = 0;
        physicsComponent.setVelocity(vel);
    }
}

void Player::render(RendererPort *renderer, const Camera &camera) const
{
    Vector2D screenPos = camera.worldToScreen(position);

    if (!animation)
    {
        std::cerr << "Error: Animation not initialized." << std::endl;
        return;
    }

    if (screenPos.x + animation->getFrameWidth() < 0 || screenPos.x > camera.getViewportWidth() ||
        screenPos.y + animation->getFrameHeight() < 0 || screenPos.y > camera.getViewportWidth())
    {
        return;
    }

    int screenX = static_cast<int>(screenPos.x);
    int screenY = static_cast<int>(screenPos.y);

    animation->render(screenX, screenY);
}

void Player::addAnimation(const std::string &name, const std::vector<int> &frameIndices)
{
    animation->addAnimation(name, frameIndices);
    std::cout << "Animação " << name << " adicionada com " << frameIndices.size() << " frames." << std::endl;
}

void Player::playAnimation(const std::string &name, bool loop)
{
    animation->playAnimation(name, loop);
}

void Player::updateAnimationBasedOnState()
{
    std::string currentAnim = animation->getCurrentAnimation();
    std::string baseAnim = currentAnim;
    
    size_t pos = baseAnim.find("Inverted");
    if (pos != std::string::npos) {
        baseAnim = baseAnim.substr(0, pos);
    }

    playAnimation(baseAnim + getCurrentStateSuffix(), true);
}
