#include <iostream>
#include <SDL2/SDL.h>
#include "adapters/SDL/SDLRendererAdapter.h"
#include "adapters/SDL/SDLEventAdapter.h"
#include "adapters/SDL/SDLPageRenderAdapter.h"
#include "domain/Game.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDLRendererAdapter renderer;
    SDLEventAdapter event;
    SDLPageRenderAdapter pageRender;
    Game game(&renderer, &event, &pageRender);
    game.run();
    SDL_Quit();
    return EXIT_SUCCESS;
}
