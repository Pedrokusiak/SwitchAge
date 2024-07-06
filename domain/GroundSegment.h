#ifndef GROUNDSEGMENT_H
#define GROUNDSEGMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"
#include "VisualElement.h"

class GroundSegment : public VisualElement {
public:
    GroundSegment(Vector2D position, float width, float height);
    void render(RendererPort* renderer) const override;
    float getWidth() const;
    float getHeight() const;

private:
    float width, height;
};

#endif // GROUNDSEGMENT_H
