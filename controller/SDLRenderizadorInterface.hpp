#include "SDL.h"
#include "Renderizador.h"

class SDLRenderizador : public Renderizador {
private:
    SDL_Renderer* renderer;
public:
    SDLRenderizador(SDL_Renderer* renderer) : renderer(renderer) {}

    void copiarBlocoPixel(void* texture, int x, int y) override {
        SDL_Texture* sdlTexture = static_cast<SDL_Texture*>(texture);
        SDL_Rect dest = {x, y, 0, 0};
        SDL_QueryTexture(sdlTexture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, sdlTexture, NULL, &dest);
    }
};
