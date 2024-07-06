#include "GroundSegment.h"
#include "VisualElement.h"

GroundSegment::GroundSegment(Vector2D position, float width, float height)
    : VisualElement(position), width(width), height(height) {}

void GroundSegment::render(RendererPort* renderer) const {
    renderer->drawRect(position.x, position.y, width, height, 0x00, 0xFF, 0x00, 0xFF);
}

float GroundSegment::getWidth() const {
    return width;
}

float GroundSegment::getHeight() const {
    return height;
}


