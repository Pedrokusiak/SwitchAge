#include "GroundSegment.h"

GroundSegment::GroundSegment(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate)
    : ObjectGame(position, size, gravity, mass, hibernate) {}

void GroundSegment::render(RendererPort* renderer) const {
    renderer->drawRect(position.x, position.y, size.x, size.y, 0x00, 0xFF, 0x00, 0xFF);
}

float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}
