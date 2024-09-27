#ifndef ISPRITE_H
#define ISPRITE_H

#include "IRenderer.h"

class ISprite {
public:
    virtual ~ISprite() {}
    virtual void update(Uint32 currentTime) = 0;
    virtual void render(IRenderer* renderer, int x, int y) = 0;
};

#endif 
