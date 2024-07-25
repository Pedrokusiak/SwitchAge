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
    hitbox.update(position); // Atualizar a hitbox após aplicar a física
}

void ObjectGame::applyPhysics(float deltaTime) {
    physicsComponent.update(deltaTime);
    position += physicsComponent.getVelocity() * deltaTime;
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}



void ObjectGame::resolveCollision(ObjectGame& other) {
        Vector2D overlap = hitbox.getOverlap(other.getHitbox());

        float const totalMass = this->physicsComponent.getMass() + other.physicsComponent.getMass();
        float const thisMassRatio = this->physicsComponent.getMass() / totalMass;
        float const otherMassRatio = other.physicsComponent.getMass() / totalMass;

        if (overlap.y < overlap.x) {
            if (position.y < other.position.y) { // Se este objeto está acima do outro (chão)
                position.y -= overlap.y; // Mover para cima, fora do chão
                physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0)); // Parar movimento vertical
            } 
        } else { 
            if (position.x < other.position.x) { 
                float const displacement = overlap.x * thisMassRatio; 
                position.x -= displacement; 
                other.position.x += overlap.x * otherMassRatio; 
            } else { 
                float const displacement = overlap.x * thisMassRatio;
                position.x += displacement; 
                other.position.x -= overlap.x * otherMassRatio; 
            }
            physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y));
            other.physicsComponent.setVelocity(Vector2D(0, other.physicsComponent.getVelocity().y));
        }
    }



