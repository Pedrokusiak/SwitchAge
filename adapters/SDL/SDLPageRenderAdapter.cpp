#include "SDLPageRenderAdapter.h"

SDLPageRenderAdapter::SDLPageRenderAdapter() {  
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDLPageRenderAdapter::~SDLPageRenderAdapter() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLPageRenderAdapter::present() const {
    SDL_RenderPresent(renderer);
}

void SDLPageRenderAdapter::quit() const {
    SDL_Quit();
}
