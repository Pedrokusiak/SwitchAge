#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector2D.h"
#include <iostream>

class Physics {
public:
    Physics(Vector2D gravity, float mass)
        : gravity(gravity), mass(mass), force(Vector2D(0,0)), acceleration(Vector2D(0,0)), velocity(Vector2D(0,0)) {}

    void applyForce(const Vector2D& force) {
        this->force += force;
    }

    void update(float deltaTime) {
        acceleration = force / mass;
        velocity += acceleration * deltaTime;
        velocity += gravity * deltaTime; 
        force = Vector2D(0,0);  
    }

    Vector2D getVelocity() const {
        return velocity;
    }

    void setVelocity(const Vector2D& vel) {
        velocity = vel;
    }

private:
    Vector2D gravity;
    float mass;
    Vector2D force;
    Vector2D acceleration;
    Vector2D velocity;
};

#endif // PHYSICS_H
