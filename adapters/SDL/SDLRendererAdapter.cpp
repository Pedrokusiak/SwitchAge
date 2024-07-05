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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void SDLRendererAdapter::drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

void SDLRendererAdapter::present() const {
    SDL_RenderPresent(renderer);
}

void SDLRendererAdapter::drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Renderer* SDLRendererAdapter::getRenderer() const {
    return renderer;
}