#include "Physics.h"
#include <iostream>

Physics::Physics(Vector2D gravity, float mass)
    : gravity(gravity), mass(mass), force(Vector2D(0, 0)), acceleration(Vector2D(0, 0)), velocity(Vector2D(0, 0)) {}

void Physics::applyForce(const Vector2D& force) {
    this->acceleration = force / mass;
    std::cout << "acc apply (" <<  this->acceleration.x << ", " <<  this->acceleration.y << ")" << std::endl;
}

void Physics::update(float deltaTime) {
    this->velocity += this->acceleration * deltaTime;
}

Vector2D Physics::getVelocity() const {
    return velocity;
}

float Physics::getMass() const {
    return mass;
}

void Physics::setVelocity(const Vector2D& vel) {
    velocity = vel;
}
