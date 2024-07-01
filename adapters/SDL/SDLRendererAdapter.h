
#ifndef SDLRENDERERADAPTER_H
#define SDLRENDERERADAPTER_H
#include <SDL2/SDL.h>
#include "ports/RendererPort.h"

class SDLRendererAdapter : public RendererPort {
public:
    SDLRendererAdapter();
    ~SDLRendererAdapter();
    void draw() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
