#include "Physics.h"
#include <iostream>
#include <cmath>

Physics::Physics(Vector2D gravity, float mass)
    : gravity(gravity), mass(mass), force(Vector2D(0, 0)), 
      acceleration(Vector2D(0, 0)), velocity(Vector2D(0, 0))
{
    if (mass == 0.0f)
    {
        throw std::invalid_argument("Mass cannot be zero.");
    }
}

void Physics::applyForce(const Vector2D& force)
{
    // Acumula forças ao invés de substituir
    this->force += force;
}

void Physics::update(float deltaTime)
{
    const float MAX_VELOCITY = 400.0f;
    const float AIR_RESISTANCE = 0.98f;
    
    // Calcula aceleração baseada em todas as forças
    acceleration = (force + gravity) / mass;
    
    // Atualiza velocidade
    velocity += acceleration * deltaTime;
    
    // Aplica resistência do ar
    velocity = velocity * AIR_RESISTANCE;
    
    // Limita velocidade máxima
    float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (currentSpeed > MAX_VELOCITY)
    {
        float scale = MAX_VELOCITY / currentSpeed;
        velocity.x *= scale;
        velocity.y *= scale;
    }
    
    // Reseta forças para o próximo frame
    force = Vector2D(0, 0);
}

float Physics::getMass() const
{
    return mass;
}

Vector2D Physics::getGravity() const
{
    return gravity;
}

Vector2D Physics::getForce() const
{
    return force;
}

Vector2D Physics::getVelocity() const
{
    return velocity;
}

Vector2D Physics::getAcceleration() const
{
    return acceleration;
}

void Physics::setVelocity(const Vector2D& vel)
{
    velocity = vel;
}

void Physics::setForce(const Vector2D& newForce)
{
    force = newForce;
}

void Physics::setAcceleration(const Vector2D& newAcceleration)
{
    acceleration = newAcceleration;
}

void Physics::setGravity(const Vector2D& newGravity)
{
    const float GRAVITY_TRANSITION_SPEED = 0.2f;
    Vector2D gravityDiff = newGravity - gravity;
    gravity += gravityDiff * GRAVITY_TRANSITION_SPEED;
}