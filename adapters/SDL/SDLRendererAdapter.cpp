#include "SDLRendererAdapter.h"

SDLRendererAdapter::SDLRendererAdapter() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDLRendererAdapter::~SDLRendererAdapter() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLRendererAdapter::draw() const {
    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 255);
    SDL_RenderClear(renderer);
}

void SDLRendererAdapter::drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

void SDLRendererAdapter::present() const {
    SDL_RenderPresent(renderer);
}

void SDLRendererAdapter::quit() const {
    SDL_Quit();
}

void SDLRendererAdapter::delay(Uint32 ms) const {
    SDL_Delay(ms);
}

Uint32 SDLRendererAdapter::getTicks() const{
    return SDL_GetTicks();
}

void SDLRendererAdapter::drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Renderer* SDLRendererAdapter::getRenderer() const {
    return renderer;
}
