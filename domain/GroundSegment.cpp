#include "GroundSegment.h"

GroundSegment::GroundSegment(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
                             std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight)
    : ObjectGame(position, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight) {}

void GroundSegment::render(RendererPort* renderer) const {
    if (texture) {
        int width = texture -> getWidth();
        int height = texture -> getHeight();
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);
        renderer->drawTexture(texture, x, y, width, height);
    }
}

float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}
