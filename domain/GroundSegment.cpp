#include "GroundSegment.h"

GroundSegment::GroundSegment(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
                             std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight)
    : ObjectGame(position, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight) {}

void GroundSegment::render(RendererPort* renderer, const Camera& camera) const {
    Vector2D screenPos = camera.worldToScreen(position);
    renderer->drawRect(screenPos.x, screenPos.y, size.x, size.y, 0x00, 0xFF, 0x00, 0xFF);
}

float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}