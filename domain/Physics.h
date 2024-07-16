#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector2D.h"

class Physics {
public:
    Physics(Vector2D gravity, float mass)
        : gravity(gravity), mass(mass), force(Vector2D()), acceleration(Vector2D()), velocity(Vector2D()) {}

    void applyForce(const Vector2D& force) {
        this->force += force;
    }

    void update(float deltaTime) {
        acceleration = force / mass;
        velocity += acceleration * deltaTime;
        velocity += gravity * deltaTime;  // Aplicar gravidade
        force = Vector2D();  // Resetar força após a atualização
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
