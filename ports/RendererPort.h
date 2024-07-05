

#ifndef RENDERERPORT_H
#define RENDERERPORT_H

#include <SDL2/SDL.h>

class RendererPort {
public:
    virtual ~RendererPort() = default;
    virtual void draw() const = 0;
    virtual void drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    virtual void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    virtual void present() const = 0;
};

#endif 
