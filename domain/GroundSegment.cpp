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

        

        int srcX = 0;            // Coordenada X de origem na textura (usualmente 0 se quiser pegar tudo)
        int srcY = 0;            // Coordenada Y de origem na textura
        int srcWidth = 256;      // Largura da parte da textura a ser desenhada
        int srcHeight = 256;     // Altura da parte da textura a ser desenhada

        renderer->drawTexturePart(texture, x, y, srcWidth, srcHeight, srcX, srcY, width, height);
    }
}



float GroundSegment::getWidth() const {
    return size.x;
}

float GroundSegment::getHeight() const {
    return size.y;
}