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
    Vector2D overlap(0, 0);

    if (intersects(other)) {
        float thisRight = position.x + size.x;
        float otherRight = other.position.x + other.size.x;
        float xMin = std::min(thisRight, otherRight);
        float xMax = std::max(position.x, other.position.x);
        overlap.x = xMin - xMax;

        float thisBottom = position.y + size.y;
        float otherBottom = other.position.y + other.size.y;
        float yMin = std::min(thisBottom, otherBottom);
        float yMax = std::max(position.y, other.position.y);
        overlap.y = yMin - yMax;
    }

    return overlap;
}
