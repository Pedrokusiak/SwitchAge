#ifndef GROUNDSEGMENT_H
#define GROUNDSEGMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"

class GroundSegment {
public:
    GroundSegment(Vector2D position, float width, float height);
    void render(RendererPort* renderer) const;
    float getWidth() const;
    float getHeight() const;
    Vector2D getPosition() const;

private:
    Vector2D position;
    float width, height;
};

#endif // GROUNDSEGMENT_HPP
