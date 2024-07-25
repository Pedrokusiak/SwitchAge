#include "Physics.h"

Physics::Physics(Vector2D gravity, float mass)
    : gravity(gravity), mass(mass), force(Vector2D(0, 0)), acceleration(Vector2D(0, 0)), velocity(Vector2D(0, 0)) {}

void Physics::applyForce(const Vector2D& force) {
    this->force += force;
}

void Physics::update(float deltaTime) {
    acceleration = force / mass;
    velocity += acceleration * deltaTime;
    velocity += gravity * deltaTime; 
    force = Vector2D(0, 0); 
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
