#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // Se estiver usando SDL_image
#include "adapters/SDL/SDLRendererAdapter.h"
#include "adapters/SDL/SDLEventAdapter.h"
#include "adapters/SDL/SDLTexture.h" 
#include "domain/Game.h"
#include <memory>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Não foi possível inicializar SDL: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    // Inicializar SDL_image (se estiver usando)
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Falha ao inicializar SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    try {
        SDLRendererAdapter renderer;

        SDLEventAdapter event;

        SDLTexture* texturePort = new SDLTexture(renderer.getRenderer());

        Camera camera(0, 0, WIDTH, HEIGHT);



        // Instanciar o Game
        Game game(&renderer, &event, texturePort, camera);
        game.run();

     
    } catch (const std::exception& e) {
        std::cerr << "Erro capturado: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Erro desconhecido capturado." << std::endl;
    }

    // Finalizar SDL_image
    IMG_Quit();

    // Finalizar SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
