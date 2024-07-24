#include "ObjectGameStatic.h"

ObjectGameStatic::ObjectGameStatic(Vector2D position, Vector2D size, Vector2D gravity, float mass)
    : ObjectGame(position, size, gravity, mass) {
}

void ObjectGameStatic::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    applyPhysics(deltaTime);
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            resolveCollision(*object);
        }
    }
}
