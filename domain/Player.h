#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "ports/RendererPort.h"
#include "Vector2D.h"
#include "Physics.h"
#include "GroundSegment.h"
#include <vector>
#include <ports/EventPort.h>
#include "VisualElement.h"

class Player : public VisualElement {
public:
    Player(Vector2D position, Vector2D size, Physics* physicsComponent);
    void handleEvent(EventPort* e);
    void move(const std::vector<GroundSegment>& groundSegments);
    void render(RendererPort* renderer) const override;

private:
    Vector2D size;
    Physics* physicsComponent;
    std::vector<GroundSegment> groundSegments;
    Vector2D velocity;
    bool onGround;
};

#endif // PLAYER_H
