#include "Physics.h"
#include <iostream>

Physics::Physics(Vector2D gravity, float mass)
    : gravity(gravity), mass(mass), force(Vector2D(0, 0)), acceleration(Vector2D(0, 0)), velocity(Vector2D(0, 0))
{
    if (mass == 0.0f)
    {
        throw std::invalid_argument("Mass cannot be zero.");
    }
    this->mass = mass;
}

void Physics::applyForce(const Vector2D &force)
{
    this->acceleration += force / mass;

    std::cout << "Current Velocity (Update Test): (" << acceleration.x << ", " << acceleration.y << ")" << std::endl;
}

void Physics::update(float deltaTime)
{

    std::cout << "Current Acceleration (Update Test): (" << acceleration.x << ", " << acceleration.y << ")" << std::endl;
    std::cout << "Current DeltaTime (Update Test): (" << deltaTime << ")" << std::endl;
    this->velocity = this->acceleration * deltaTime;

    std::cout << "Current Velocity (Update Test): (" << velocity.x << ", " << velocity.y << ")" << std::endl;
    applyForce(gravity);
}

Vector2D Physics::getVelocity() const
{
    return velocity;
}

Vector2D Physics::getGravity() const
{
    return gravity;
}

float Physics::getMass() const
{
    return mass;
}

void Physics::setVelocity(const Vector2D &vel)
{
    velocity = vel;
}

void Physics::setGravity(const Vector2D &gravity)
{
    this->gravity = gravity;
}

void Physics::setForce(const Vector2D &force)
{
    this->force = force;
}
