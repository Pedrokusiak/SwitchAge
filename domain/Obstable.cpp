#include "Obstacle.h"
#include "Vector2D.h"
#include "RendererPort.h"

Obstacle::Obstacle(Vector2D position, float width, float height)
    : position(position), width(width), height(height) {}

void Obstacle::render(RendererPort *renderer) const
{
    renderer->drawRect(position.x, position.y, width, height, 255, 0, 0, 255);
}

Vector2D Obstacle::getPosition() const
{
    return position;
}

float Obstacle::getWidth() const
{
    return width;
}

float Obstacle::getHeight() const
{
    return height;
}
