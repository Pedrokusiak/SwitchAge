#ifndef SDLPAGERENDERPORT_H
#define SDLPAGERENDERPORT_H

#include <SDL2/SDL.h>
#include <ports/PageRenderPort.h>

class SDLPageRenderAdapter : public PageRenderPort {
    public:
        SDLPageRenderAdapter();
        ~SDLPageRenderAdapter();
        void present() const override;
        void quit() const override;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif // SDLPAGERENDERPORT_H
