#include "Game.h"
#include <adapters/SDL/SDLEventAdapter.h>
#include <adapters/SDL/SDLRendererAdapter.h>

Game::Game(RendererPort *renderer, EventPort *eventPort)
    : renderer(renderer),
    eventPort(eventPort),
    playerPhysics(0.5f, 10.0f, 15.0f),
    player(
        Vector2D(50, 50), 
        Vector2D(50, 50), 
        &playerPhysics) {
    // Inicializa segmentos do chão
    groundSegments.push_back(GroundSegment(Vector2D(0, 580), 800, 20));
    // Adicione mais segmentos conforme necessário
}

void Game::run() {
    bool running = true;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (running) {
        frameStart = SDL_GetTicks();

        while (eventPort -> pollEvent()) {
            if (eventPort -> isQuitEvent()) {
                running = false;
            }
            player.handleEvent(eventPort); // Passa o adaptador de evento para o jogador
        }

        player.move(groundSegments);  // Passa os segmentos do chão para verificar a colisão

        renderer->draw(); // Desenha o fundo

        player.render(renderer); // Renderiza o jogador
        for (const auto& segment : groundSegments) {
            segment.render(renderer); // Renderiza cada segmento do chão
        }

        renderer->present(); 


        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_Quit();
}
