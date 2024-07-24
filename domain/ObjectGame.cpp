#include "ObjectGameStatic.h"
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
    hitbox.update(position); 
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame& other) {
    if (checkCollision(other)) {
        Vector2D overlap = hitbox.getOverlap(other.getHitbox());

        ObjectGameStatic* staticObject = dynamic_cast<ObjectGameStatic*>(&other);
        if (staticObject) {
            // Se o outro objeto for ObjectGameStatic, apenas o objeto atual tem sua posição atualizada
            position -= overlap;
        } else {
            // Se ambos os objetos são móveis, ambos têm suas posições e velocidades atualizadas
            position -= overlap / 2;
            other.position += overlap / 2;

            Vector2D tempVelocity = physicsComponent.getVelocity();
            physicsComponent.setVelocity(other.physicsComponent.getVelocity());
            other.physicsComponent.setVelocity(tempVelocity);
        }

        hitbox.update(position);
        if (!staticObject) {
            other.hitbox.update(other.position);
        }
    }
}
