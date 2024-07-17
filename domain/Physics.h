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
        std::cout << "Velocity: Update INTO until sum (" << velocity.x << ", " << velocity.y << ")" << std::endl;
        velocity += acceleration * deltaTime;
        std::cout << "Velocity: Update INTO until acceleration (" << velocity.x << ", " << velocity.y << ")" << std::endl;
        velocity += gravity * deltaTime; 
        std::cout << "Velocity: Update INTO until gravity (" << velocity.x << ", " << velocity.y << ")" << std::endl;
        std::cout << "Velocity: Update INTO (" << velocity.x << ", " << velocity.y << ")" << std::endl;
         // Aplicar gravidade
        force = Vector2D(0,0);  // Resetar força após a atualização
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
