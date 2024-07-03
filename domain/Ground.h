#ifndef GROUND_H
#define GROUND_H

#include "Position.h"
#include "Physics.h"
#include "ports/RendererPort.h"

class Ground {
public:
    Ground(Position position, int width, int height, Physics* physicsComponent);
    void render(RendererPort* renderer);

private:
    Position position;
    Physics* physicsComponent;
    int width, height;
};

#endif // GROUND_HPP
