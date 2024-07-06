#ifndef VISUALELEMENT_H
#define VISUALELEMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"

class VisualElement {
public:
    VisualElement(Vector2D pos);
    virtual ~VisualElement() = default;

    virtual void render(RendererPort* renderer) const = 0;

    Vector2D getPosition() const;
    void setPosition(const Vector2D& pos);

protected:
    Vector2D position;
};

#endif // VISUALELEMENT_H
