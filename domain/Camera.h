// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

class Camera {
public:
    Camera(float x, float y, int viewportWidth, int viewportHeight);

    void centerOn(const Vector2D& target);
    Vector2D worldToScreen(const Vector2D& worldPos) const;
    Vector2D screenToWorld(const Vector2D& screenPos) const;

    void setPosition(const Vector2D& newPos);
    Vector2D getPosition() const;

    int getViewportWidth() const;
    int getViewportHeight() const;

private:
    Vector2D position;
    int viewportWidth;
    int viewportHeight;
};

#endif // CAMERA_H