#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#include <iostream>
#include "controller/implentacaoController/TelaController.cpp"
#include "controller/implentacaoController/RenderizadorController.cpp"
#include "models/implentacao/Tela.cpp"


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    // Crie uma instância de RenderizadorController
    SDL_Window* window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    RenderizadorController renderizadorController(renderer);

    // Crie uma instância de TelaController
    Tela tela; 
    tela.setJanela(window);
 
    
    // Suponha que você tenha definido a estrutura Tela
    TelaController telaController(&tela, &renderizadorController);

    // Exemplo de uso
    telaController.preparaCenario();
    // Outras operações ...

    SDL_Delay(2000); // Aguarda 2 segundos antes de fechar a janela
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
};


