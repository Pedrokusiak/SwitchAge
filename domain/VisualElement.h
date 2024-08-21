#ifndef VISUALELEMENT_H
#define VISUALELEMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"
#include "Camera.h"

class VisualElement {
public:
    VisualElement(Vector2D position);
    virtual ~VisualElement() = default;

    virtual void render(RendererPort* renderer, const Camera& camera) const = 0;

    Vector2D getPosition() const;
    void setPosition(const Vector2D& position);

protected:
    Vector2D position;
};

#endif // VISUALELEMENT_H
