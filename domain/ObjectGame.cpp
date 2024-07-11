#include "ObjectGame.h"


ObjectGame::ObjectGame(Vector2D pos, Vector2D size, Physics* physicsComponent)
    : VisualElement(pos), size(size), physicsComponent(physicsComponent), velocity(0, 0) {}


void ObjectGame::move(const std::vector<GroundSegment>& groundSegments, float deltatime) {
    physicsComponent-> update(
        deltatime
    );
}

void ObjectGame::render(RendererPort* renderer) const {
    renderer->drawPlayer(position.x, position.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
