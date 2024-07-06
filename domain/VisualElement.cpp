#include "VisualElement.h"

VisualElement::VisualElement(Vector2D pos) : position(pos) {}

Vector2D VisualElement::getPosition() const {
    return position;
}

void VisualElement::setPosition(const Vector2D& pos) {
    position = pos;
}
