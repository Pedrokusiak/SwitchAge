#include <SDL2/SDL.h>
#include "domain/Game.h"

Game::Game(RendererPort* renderer) : renderer(renderer) {}

void Game::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
    bool running = true;
    SDL_Event event;
    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer->draw();

        // Calcular o tempo gasto em milissegundos
        frameTime = SDL_GetTicks() - frameStart;

        // Se o frame processar mais rápido que o tempo desejado por frame, adiciona um atraso
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    }
}
