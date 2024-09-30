#include "GroundSegment.h"

GroundSegment::GroundSegment(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
                             std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight)
    : ObjectGame(position, size, gravity, mass, hibernate, texture, renderer, frameWidth, frameHeight) {}



void GroundSegment::render(RendererPort* renderer, const Camera& camera) const {
    if (texture) {
        Vector2D screenPos = camera.worldToScreen(position);
        int x = static_cast<int>(screenPos.x);
        int y = static_cast<int>(screenPos.y);
        int width = static_cast<int>(size.x);
        int height = static_cast<int>(size.y);

        if (x + width < 0 || x > camera.getViewportWidth() ||
            y + height < 0 || y > camera.getViewportHeight()) {
            return;  // Segmento está fora da viewport, não renderize
        }

        renderer->drawTexture(texture, x, y, width, height);
    }
}



float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}