#include "Physics.h"
#include <iostream>

Physics::Physics(Vector2D gravity, float mass)
    : gravity(gravity), mass(mass), force(Vector2D(0, 0)), acceleration(Vector2D(0, 0)), velocity(Vector2D(0, 0)) {}

void Physics::applyForce(const Vector2D& force) {

   

    this->acceleration += force / mass;

     std::cout << "acceleration: (" << acceleration.x << ", " << acceleration.y << ")\n";
}

void Physics::update(float deltaTime) {
    this->velocity = this->acceleration * deltaTime;
    applyForce(gravity);
}

Vector2D Physics::getVelocity() const {
    return velocity;
}

Vector2D Physics::getGravity() const {
    return gravity;
}

float Physics::getMass() const {
    return mass;
}

void Physics::setVelocity(const Vector2D& vel) {
    velocity = vel;
}

void Physics::setGravity(const Vector2D& gravity) {
    this -> gravity = gravity;
}



