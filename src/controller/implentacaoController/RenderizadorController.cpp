#include <iostream>
#include <SDL.h>
#include "Renderizador.h"
#include "RenderizadorControllerInterface.h"

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

    void preparaCenario(){
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);
    }

    void cenaPresente(){
        SDL_RenderPresent(renderer);
    }
};
