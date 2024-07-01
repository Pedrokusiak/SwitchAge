#include <SDL2/SDL.h>
#include "domain/Game.h"

Game::Game(RendererPort* renderer) : renderer(renderer) {}

void Game::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer->draw();
        SDL_Delay(16);
    }
}
