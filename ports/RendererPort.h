

#ifndef RENDERERPORT_H
#define RENDERERPORT_H
#include <SDL2/SDL.h>
#include "ITexture.h"

class RendererPort {
public:
    virtual ~RendererPort() = default;

    
    virtual void draw() const = 0;


    virtual void drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    
    // Draw rect port -> RectRenderPort
    virtual void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    
    // Initial page -> PageRenderPort
    virtual void present() const = 0;
    virtual void quit() const = 0;

    // Timer action -> TimeRenderPort
    virtual void delay(Uint32 tempo) const = 0;
    virtual Uint32 getTicks() const = 0;
    
    virtual void drawTexture(ITexture* texture, int x, int y, int width, int height) = 0;
};

#endif 
