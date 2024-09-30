#include "VisualElement.h"

VisualElement::VisualElement(Vector2D pos, const std::shared_ptr<ITexture>& texture)
    : position(pos), texture(texture) {}

void VisualElement::render(RendererPort* renderer, const Camera& camera) const {
    if (texture) {
        int width = texture->getWidth();
        int height = texture->getHeight();
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);
        renderer->drawTexture(texture, x, y, width, height);
    }
}
