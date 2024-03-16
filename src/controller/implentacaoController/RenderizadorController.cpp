#include <iostream>
#include "SDL.h"
#include "../RenderizadorControllerInterface.hpp"

class RenderizadorController : public RenderizadorControllerInterface {
private:
    SDL_Renderer* renderer;
    SDL_Window *janela;

public:
    RenderizadorController(SDL_Renderer* renderer) : renderer(renderer) {}

    void copiarBlocoPixel(void* texture, int x, int y) override {
        SDL_Texture* sdlTexture = static_cast<SDL_Texture*>(texture);
        SDL_Rect dest = {x, y, 0, 0};
        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, sdlTexture, NULL, &dest);
    }

    void preparaCenario() override {
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);
    }

    void cenaPresente() override {
        SDL_RenderPresent(renderer);
    }
};
