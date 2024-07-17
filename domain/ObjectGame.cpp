#include "ObjectGame.h"

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass)
    : VisualElement(position), size(size), physicsComponent(gravity, mass), hitbox(position, size) {}

void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    applyPhysics(deltaTime);
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            resolveCollision(*object);
        }
    }
}

void ObjectGame::applyPhysics(float deltaTime) {
    physicsComponent.update(deltaTime);
    position += physicsComponent.getVelocity() * deltaTime;
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame& other) {
    if (checkCollision(other)) {
        Vector2D overlap = hitbox.getOverlap(other.getHitbox());
        position -= overlap / 2;
        other.position += overlap / 2;

        Vector2D tempVelocity = physicsComponent.getVelocity();
        physicsComponent.setVelocity(other.physicsComponent.getVelocity());
        other.physicsComponent.setVelocity(tempVelocity);
    }
}
