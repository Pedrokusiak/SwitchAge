#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include <SDL2/SDL.h>
#include "ports/RendererPort.h"
#include "Vector2D.h"
#include "Physics.h"
#include "GroundSegment.h"
#include <vector>
#include <ports/EventPort.h>
#include "VisualElement.h"

class ObjectGame : public VisualElement {
public:
    ObjectGame(Vector2D position, Vector2D size, Physics* physicsComponent);
    virtual void move(const std::vector<GroundSegment>& groundSegments, float deltaTime);
    void render(RendererPort* renderer) const override;

private:
    Vector2D size;
    Physics* physicsComponent;
    Vector2D velocity;

};

#endif 
