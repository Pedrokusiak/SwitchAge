#include "ObjectGame.h"
#include <iostream>

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass)
    : VisualElement(position), size(size), physicsComponent(gravity, mass), hitbox(position, size) {}

void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    applyPhysics(deltaTime);
   
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            resolveCollision(*object);
        }
    }
    hitbox.update(position); // Atualizar a hitbox após aplicar a física
}

void ObjectGame::applyPhysics(float deltaTime) {
    physicsComponent.update(deltaTime);
    position += physicsComponent.getVelocity() * deltaTime;
    std::cout << "pos physics: (" << position.x << ", " << position.y << ")" << std::endl;
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame& other) {
    if (checkCollision(other)) {
        Vector2D overlap = hitbox.getOverlap(other.getHitbox());
        if (overlap.y < overlap.x) {
            if (position.y < other.position.y) {
                position.y -= overlap.y; 
                physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0)); 
            } 
        } else { 
            if (position.x < other.position.x) {
                position.x -= overlap.x; 
            } else {
                position.x += overlap.x; 
            }
            physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y));
        }
    }
}
