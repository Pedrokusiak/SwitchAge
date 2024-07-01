#include <iostream>
#include <SDL2/SDL.h>
#include "adapters/SDL/SDLRendererAdapter.h"
#include "domain/Game.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDLRendererAdapter renderer;
    Game game(&renderer);
    game.run();
    SDL_Quit();
    return EXIT_SUCCESS;
}
