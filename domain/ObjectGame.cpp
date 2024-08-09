#include "ObjectGame.h"
#include <tuple>
#include <set>
#include <vector>
#include <iostream>
#include <memory>

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hiberate)
    : VisualElement(position), size(size), physicsComponent(gravity, mass), hitbox(position, size) {}

void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    applyPhysics(deltaTime);
    if(!hibernate){
        hitbox.update(position);
    }
    std::set<std::tuple<int, int>> checkedPairs;
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < gameObjects.size(); ++j) {
            auto pair = std::make_tuple(i, j);

            if (checkedPairs.find(pair) == checkedPairs.end()) {
                checkedPairs.insert(pair);

                if (gameObjects[i]->checkCollision(*gameObjects[j])) {
                    gameObjects[i]->resolveCollision(*gameObjects[j]);
                }
            }
        }
    }
}

void ObjectGame::applyPhysics(float deltaTime) {
    if(!hibernate){
        physicsComponent.update(deltaTime);
        position += physicsComponent.getVelocity() * deltaTime;
    }
  
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame& other) {
    Vector2D overlap = hitbox.getOverlap(other.getHitbox());

    float const totalMass = this->physicsComponent.getMass() + other.physicsComponent.getMass();
    float const thisMassRatio = this->physicsComponent.getMass() / totalMass;
    float const otherMassRatio = other.physicsComponent.getMass() / totalMass;

    // Debugging information
    std::cout << "overlap: (" << overlap.x << ", " << overlap.y << ")\n";
    std::cout << "positions before collision: this(" << position.x << ", " << position.y << ") other(" << other.position.x << ", " << other.position.y << ")\n";
    std::cout << "velocities before collision: this(" << physicsComponent.getVelocity().x << ", " << physicsComponent.getVelocity().y << ") other(" << other.physicsComponent.getVelocity().x << ", " << other.physicsComponent.getVelocity().y << ")\n";

    // Reset gravity effect during collision calculations
    Vector2D originalGravity = this->physicsComponent.getGravity();
    this->physicsComponent.setGravity(Vector2D(0, 0));
    other.physicsComponent.setGravity(Vector2D(0, 0));

    // Vertical collision resolution
    if (overlap.y < overlap.x) {
        if (position.y < other.position.y) {  // This object is above the other
            position.y -= overlap.y;  // Move this object up by overlap amount
            physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, 0));  // Stop vertical movement

            std::cout << "Correcting vertical overlap from above. New y-position: " << position.y << "\n";
        } else {  
            other.position.y -= overlap.y;  // Move the other object up
            other.physicsComponent.setVelocity(Vector2D(other.physicsComponent.getVelocity().x, 0));  // Stop the other object's vertical movement

            std::cout << "Correcting vertical overlap from below. New y-position of other: " << other.position.y << "\n";
        }
    } else {
        // Horizontal collision resolution (similar logic)
        float displacement = overlap.x * thisMassRatio;
        if (position.x < other.position.x) {
            position.x -= displacement;
            other.position.x += overlap.x * otherMassRatio;
        } else {
            position.x += displacement;
            other.position.x -= overlap.x * otherMassRatio;
        }

        // Reset horizontal velocities
        physicsComponent.setVelocity(Vector2D(0, 0));
        other.physicsComponent.setVelocity(Vector2D(0, 0));
    }



  
}




