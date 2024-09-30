#include "Camera.h"

Camera::Camera(float x, float y, int viewportWidth, int viewportHeight)
    : position(x, y), viewportWidth(viewportWidth), viewportHeight(viewportHeight) {}

void Camera::centerOn(const Vector2D& target) {
    position.x = target.x - viewportWidth / 2;
    position.y = target.y - viewportHeight / 2;
}

Vector2D Camera::worldToScreen(const Vector2D& worldPos) const {
    return Vector2D(worldPos.x - position.x, worldPos.y - position.y);
}

Vector2D Camera::screenToWorld(const Vector2D& screenPos) const {
    return Vector2D(screenPos.x + position.x, screenPos.y + position.y);
}

void Camera::setPosition(const Vector2D& newPos) {
    position = newPos;
}

Vector2D Camera::getPosition() const {
    return position;
}

int Camera::getViewportWidth() const {
    return viewportWidth;
}

int Camera::getViewportHeight() const {
    return viewportHeight;
}