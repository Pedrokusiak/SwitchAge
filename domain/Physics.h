#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector2D.h"

class Physics {
public:
    Physics(Vector2D gravity, float mass);

    void applyForce(const Vector2D& force);
    void update(float deltaTime);

    float getMass() const;
    Vector2D getGravity() const;
    Vector2D getForce() const { return force; }
    Vector2D getVelocity() const;
    Vector2D getAcceleration() const { return acceleration;}
    void setVelocity(const Vector2D& vel);
    void setForce(const Vector2D& force);
    void setAcceleration(const Vector2D& acceleration){
        this -> acceleration = acceleration;
    }
    


    void setGravity(const Vector2D& gravit);

private:
    Vector2D gravity;
    float mass;
    Vector2D force;
    Vector2D acceleration;
    Vector2D velocity;
};

#endif // PHYSICS_H
