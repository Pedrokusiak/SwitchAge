#ifndef VISUALELEMENT_H
#define VISUALELEMENT_H

#include "Vector2D.h"
#include "ports/RendererPort.h"
#include "ports/ITexture.h"
#include "memory"

class VisualElement {
public:
    VisualElement(Vector2D position,const  std::shared_ptr<ITexture>& texture);
    virtual ~VisualElement() = default;

    virtual void render(RendererPort* renderer) const;

    Vector2D getPosition() const { return position; }
    void setPosition(const Vector2D& position) { this->position = position; }

protected:
    Vector2D position;
    std::shared_ptr<ITexture> texture;
};

#endif // VISUALELEMENT_H
