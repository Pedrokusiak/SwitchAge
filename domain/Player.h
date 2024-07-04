#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "ports/RendererPort.h"
#include "Vector2D.h"
#include "Physics.h"
#include "GroundSegment.h"
#include <vector>
#include <ports/EventPort.h>

class Player {
public:
    Player(Vector2D position, Vector2D size, Physics* physicsComponent);
    void handleEvent(EventPort* e);
    void move(const std::vector<GroundSegment>& groundSegments);
    void render(RendererPort* renderer) const;

private:
    Vector2D position;
    Vector2D size;
    Physics* physicsComponent;
    std::vector<GroundSegment> groundSegments; // Certifique-se de declarar aqui
    Vector2D velocity;
    bool onGround;
};

#endif // PLAYER_H
