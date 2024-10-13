#include "ObjectGame.h"
#include <tuple>
#include <set>
#include <vector>
#include <iostream>
#include <memory>

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate,
                       std::shared_ptr<ITexture> texture, RendererPort *renderer, int frameWidth, int frameHeight)
    : VisualElement(position, texture),
      size(size),
      physicsComponent(gravity, mass),
      hitbox(position, size),
      hibernate(hibernate),
      animation(std::make_unique<Animation>(renderer, texture, frameWidth, frameHeight)) {}

void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>> &gameObjects)
{
    if (hibernate) return;

    applyPhysics(deltaTime);
    animation->update(deltaTime);

    for (const auto& other : gameObjects)
    {
        if (other.get() != this && checkCollision(*other))
        {
            resolveCollision(*other);
        }
    }
}


void ObjectGame::applyPhysics(float deltaTime)
{
    if (!hibernate)
    {
        physicsComponent.update(deltaTime);
        position += physicsComponent.getVelocity() * deltaTime;

        hitbox.update(position);
    }
}

bool ObjectGame::checkCollision(const ObjectGame &other) const
{
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame &other)
{
    Vector2D overlap = hitbox.getOverlap(other.getHitbox());
    
    if (overlap.x == 0 && overlap.y == 0) return; // No collision

    // Determine collision direction
    bool fromTop = position.y < other.position.y;
    bool fromLeft = position.x < other.position.x;

    // Resolve collision
    if (std::abs(overlap.x) < std::abs(overlap.y))
    {
        // Horizontal collision
        position.x += fromLeft ? -overlap.x : overlap.x;
        physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y));
    }
    else
    {
        // Vertical collision
        position.y += fromTop ? -overlap.y : overlap.y;
        
        if (fromTop)
        {
            // Landing on a surface
            physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0));
            physicsComponent.setGravity(Vector2D(0, 0));
        }
        else
        {
            // Hitting a ceiling
            physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0));
        }
    }

    // Update hitbox
    hitbox.update(position);
}

void ObjectGame::handleHibernateCollision(ObjectGame &other, const Vector2D &overlap)
{
    if (this->hibernate && !other.hibernate)
    {
        other.adjustForCollision(other, overlap);
    }
    else if (!this->hibernate && other.hibernate)
    {
        this->adjustForCollision(other, overlap);
    }
}

void ObjectGame::adjustForCollision(ObjectGame &other, const Vector2D &overlap)
{

    bool isHorizontal = overlap.x < overlap.y;

    if (isHorizontal)
    {
        if (position.x < other.getPosition().x)
        {
            position.x -= overlap.x; // Empurra para a esquerda
        }
        else
        {
            position.x += overlap.x; // Empurra para a direita
        }
        physicsComponent.setGravity(Vector2D(0, 0));
        physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y)); // Anula a velocidade horizontal para evitar que continue movendo-se para dentro do objeto
    }
    else
    {
        if (position.y < other.getPosition().y)
        {
            position.y -= overlap.y; // Empurra para cima
        }
        physicsComponent.setVelocity(Vector2D(0, 0));
        physicsComponent.setGravity(Vector2D(0, 0)); // Anula a velocidade vertical para evitar que continue movendo-se para dentro do objeto
    }
}
