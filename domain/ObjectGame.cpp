#include "ObjectGame.h"
#include <tuple>
#include <set>
#include <vector>
#include <iostream>
#include <memory>

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
                       std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight)
    : VisualElement(position, texture), 
      size(size), 
      physicsComponent(gravity, mass), 
      hitbox(position, size),
      hibernate(hibernate),
      animation(std::make_unique<Animation>(renderer, texture, frameWidth, frameHeight)) {}


void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    std::cout << "TESTE - Frame Timer: " << deltaTime << std::endl;

    applyPhysics(deltaTime);
    animation->update(deltaTime); 
   
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
     if (!hibernate) {
        physicsComponent.update(deltaTime);
        position += physicsComponent.getVelocity() * deltaTime;

        hitbox.update(position);
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

    // Vertical collision resolution
    if (overlap.y < overlap.x) {
        if (position.y < other.position.y) {  // This object is above the other
            position.y -= overlap.y;  // Move this object up by overlap amount
            
            physicsComponent.applyForce(Vector2D(physicsComponent.getForce().x, -physicsComponent.getForce().y * 2));
            physicsComponent.setAcceleration(Vector2D(physicsComponent.getAcceleration().x,0));
            other.physicsComponent.setAcceleration(Vector2D(other.physicsComponent.getAcceleration().x,0));
            physicsComponent.setGravity(Vector2D(0,0));
            physicsComponent.setVelocity(Vector2D(0,0));
            std::cout << "Correcting vertical overlap from above. New y-position: " << position.y << "\n";
        } else {  
            other.position.y -= overlap.y;  // Move the other object up
            physicsComponent.setAcceleration(Vector2D(physicsComponent.getAcceleration().x,0));
            other.physicsComponent.setAcceleration(Vector2D(other.physicsComponent.getAcceleration().x,0));
            physicsComponent.setGravity(Vector2D(0,0));
            physicsComponent.applyForce(Vector2D(physicsComponent.getForce().x, -physicsComponent.getForce().y * 2));
            std::cout << "Correcting vertical overlap from below. New y-position of other: " << other.position.y << "\n";
        }

        std::cout << "State after applying forces:" << std::endl;
        std::cout << "This object force after adjustment: (" << physicsComponent.getForce().x << ", " << physicsComponent.getForce().y << ")" << std::endl;
        std::cout << "This object force 2 adjustment: (" << other.physicsComponent.getForce().x << ", " << other.physicsComponent.getForce().y << ")" << std::endl;

    } else {
        // Horizontal collision resolution (similar logic)
        float displacement = overlap.x * thisMassRatio;
        if (position.x < other.position.x) {
             // Horizontal collision resolution (similar logic)
        float displacement = overlap.x * thisMassRatio;
        if (position.x < other.position.x) {
            position.x -= displacement;
            other.position.x += overlap.x * otherMassRatio;
        } else {
            position.x += displacement;
            other.position.x -= overlap.x * otherMassRatio;
        }
        }
    }

    std::cout << "velocities after collision: this(" << physicsComponent.getVelocity().x << ", " << physicsComponent.getVelocity().y << ") other(" << other.physicsComponent.getVelocity().x << ", " << other.physicsComponent.getVelocity().y << ")\n";

}

void ObjectGame::handleHibernateCollision(ObjectGame& other, const Vector2D& overlap) {
    if (this->hibernate && !other.hibernate) {
        other.adjustForCollision(other,overlap);
    } else if (!this->hibernate && other.hibernate) {
        this->adjustForCollision(other,overlap);
    }
}

void ObjectGame::adjustForCollision(ObjectGame& other,const Vector2D& overlap) {

    bool isHorizontal = overlap.x < overlap.y;

    if (isHorizontal) {
        if (position.x < other.getPosition().x) {
            position.x -= overlap.x; // Empurra para a esquerda
        } else {
            position.x += overlap.x; // Empurra para a direita
        }
        physicsComponent.setGravity(Vector2D(0,0));
        physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y)); // Anula a velocidade horizontal para evitar que continue movendo-se para dentro do objeto
    } else {
        if (position.y < other.getPosition().y) {
            position.y -= overlap.y; // Empurra para cima
        } 
        physicsComponent.setVelocity(Vector2D(0, 0));
        physicsComponent.setGravity(Vector2D(0,0)); // Anula a velocidade vertical para evitar que continue movendo-se para dentro do objeto
    }
}

