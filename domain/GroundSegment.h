#ifndef GROUNDSEGMENT_H
#define GROUNDSEGMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"
#include "ObjectGame.h"

class GroundSegment : public ObjectGame {
public:
    GroundSegment(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate);
    void render(RendererPort* renderer) const override;
    float getWidth() const;
    float getHeight() const;
};

#endif // GROUNDSEGMENT_H
