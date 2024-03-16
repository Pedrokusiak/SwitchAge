#include <iostream>
#include "../RenderizadorControllerInterface.hpp"
#include "../TelaControllerInterface.hpp"
#include "SDL.h"
#include "../../models/TelaInterface.hpp"

class TelaController : public TelaControllerInterface{
    private:
    TelaInterface* tela;
    RenderizadorControllerInterface* renderizador;      

    public:
    TelaController(TelaInterface* tela, RenderizadorControllerInterface* renderizador) : tela(tela, renderizador) {}
    virtual ~TelaController() {
        int rendererFlags, windowFlags;
        rendererFlags = SDL_RENDERER_ACCELERATED;
        windowFlags = 0;
        
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }
        renderizador.janela = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
        if (!tela.window) {
            printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        renderizador.renderer = SDL_CreateRenderer(renderizador.janela, -1, rendererFlags);
        if (!renderizador.renderer) {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            exit(1);
        }
    }
    
    

    void processarEventos() {
        std::cout << "Tela Controller: Processando eventos." << std::endl;
    }

    void preparaCenario() {
        std::cout << "Tela Controller: Preparando Cenario." << std::endl;
        renderizador->preparaCenario();
    }

    void copiarBlocoPixel() {
        std::cout << "Tela Controller: copiarBlocoPixel." << std::endl;
        renderizador->copiarBlocoPixel();
    }
}

TelaController:: 
