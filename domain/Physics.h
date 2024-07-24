#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector2D.h"

class Physics {
public:
    Physics(Vector2D gravity, float mass);

    void applyForce(const Vector2D& force);
    void update(float deltaTime);

    Vector2D getVelocity() const;
    void setVelocity(const Vector2D& vel);

private:
    Vector2D gravity;
    float mass;
    Vector2D force;
    Vector2D acceleration;
    Vector2D velocity;
};

#endif // PHYSICS_H
