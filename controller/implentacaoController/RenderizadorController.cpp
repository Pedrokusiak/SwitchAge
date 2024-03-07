#include "SDL.h"
#include "Renderizador.h"

class RenderizadorController : public RenderizadorControllerInterface {
private:
    SDL_Renderer* renderer;
public:
    RenderizadorController(SDL_Renderer* renderer) : renderer(renderer) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }
        app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
        if (!app.window) {
            printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
        if (!app.renderer) {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            exit(1);
        }
    }

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
