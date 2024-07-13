#include "GroundSegment.h"

GroundSegment::GroundSegment(Vector2D position, Vector2D size, Physics* physics)
    : ObjectGame(position, size, physics) {} // O chão não precisa de física

void GroundSegment::render(RendererPort* renderer) const {
    renderer->drawRect(position.x, position.y, size.x, size.y, 0x00, 0xFF, 0x00, 0xFF);
}

float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}
