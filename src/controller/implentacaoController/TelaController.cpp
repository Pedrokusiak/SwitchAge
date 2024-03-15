#include <iostream>
#include "src/controller/implentacaoController/RenderizadorController.cpp"
#include "src/controller/TelaControllerInterface.hpp"

class TelaController : public TelaControllerInterface{
    private:
    Tela* tela;
    RenderizadorController* renderizador;      

    public:
    TelaController(Tela* tela, RenderizadorController* renderizador) : tela(tela, renderizador) {}
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
    
    

    void processarEventos() override {
        std::cout << "Tela Controller: Processando eventos." << std::endl;
    }

    void preparaCenario() override {
        std::cout << "Tela Controller: Preparando Cenario." << std::endl;
        renderizador->preparaCenario();
    }

    void copiarBlocoPixel() override {
        std::cout << "Tela Controller: copiarBlocoPixel." << std::endl;
        renderizador->copiarBlocoPixel();
    }
}

TelaController:: 
