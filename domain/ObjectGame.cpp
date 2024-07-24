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
    if (checkCollision(other)) {
        Vector2D overlap = hitbox.getOverlap(other.getHitbox());

        // Supondo que 'other' seja o chão e deve ser estático
        // Se a colisão é vertical (com o chão)
        if (overlap.y < overlap.x) {
            if (position.y < other.position.y) { // Se este objeto está acima do outro (chão)
                position.y -= overlap.y; // Mover para cima, fora do chão
                physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0)); // Parar movimento vertical
            } 
        } else { // Se a colisão é horizontal
            if (position.x < other.position.x) { // Este objeto está à esquerda do outro
                position.x -= overlap.x; // Mover para a esquerda
            } else { // Este objeto está à direita do outro
                position.x += overlap.x; // Mover para a direita
            }
            // Parar movimento horizontal
            physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y));
        }
    }
}
