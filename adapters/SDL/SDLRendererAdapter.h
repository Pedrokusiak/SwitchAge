
#ifndef SDLRENDERERADAPTER_H
#define SDLRENDERERADAPTER_H
#include <SDL2/SDL.h>
#include "ports/RendererPort.h"

class SDLRendererAdapter : public RendererPort {
public:
    SDLRendererAdapter();
    ~SDLRendererAdapter();
    void draw() const;
    void drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void present() const override;
    
    void quit() const override;

    void delay(Uint32 ms) const override;
    Uint32 getTicks() const override;
    SDL_Renderer *getRenderer() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
