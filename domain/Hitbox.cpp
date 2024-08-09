#include "Hitbox.h"
#include <iostream>

Hitbox::Hitbox(Vector2D position, Vector2D size)
    : position(position), size(size) {}

void Hitbox::update(Vector2D newPosition) {
    position = newPosition;
}

bool Hitbox::intersects(const Hitbox& other) const {
    float thisRight = position.x + size.x;
    float otherRight = other.position.x + other.size.x;
    bool xOverlap = position.x < otherRight && thisRight > other.position.x;
    
    float thisBottom = position.y + size.y;
    float otherBottom = other.position.y + other.size.y;
    bool yOverlap = position.y < otherBottom && thisBottom > other.position.y;
    
    return xOverlap && yOverlap;
}

Vector2D Hitbox::getOverlap(const Hitbox& other) const {
    if (!intersects(other)) {
        return Vector2D(0, 0);
    }
    float thisRight = getPosition().x + getSize().x;
    float otherRight = other.getPosition().x + other.getSize().x;
    float thisBottom = getPosition().y + getSize().y;
    float otherBottom = other.getPosition().y + other.getSize().y;

    float xMin = std::min(thisRight, otherRight);
    float xMax = std::max(getPosition().x, other.getPosition().x);
    float yMin = std::min(thisBottom, otherBottom);
    float yMax = std::max(getPosition().y, other.getPosition().y);

    return Vector2D(xMin - xMax, yMin - yMax);
}