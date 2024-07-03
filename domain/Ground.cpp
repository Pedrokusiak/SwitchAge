#include "Ground.h"
#include "Physics.h"

Ground::Ground(Position pos, int width, int height, Physics* physicsComponent)
    : position(pos), width(width), height(height), physicsComponent(physicsComponent) {}

void Ground::render(RendererPort* renderer) {
    renderer->drawPlayer(position.getPositionX(), position.getPositionY(), width, height, 0x00, 0xFF, 0x00, 0xFF);
}
