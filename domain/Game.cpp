#include "Game.h"
#include "GroundSegment.h"
#include <adapters/SDL/SDLEventAdapter.h>
#include <adapters/SDL/SDLRendererAdapter.h>

Game::Game(RendererPort *renderer, EventPort *eventPort)
    : renderer(renderer),
      eventPort(eventPort),
      player(Vector2D(50, 50), Vector2D(50, 50), new Physics(Vector2D(0, 9.8f), 1.0f)) {
    // Inicializa segmentos do chão
    groundSegments.push_back(GroundSegment(Vector2D(0, 580), Vector2D(800, 20), nullptr));
    // Adicione mais segmentos conforme necessário
}

void Game::run() {
    bool running = true;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 45;
    const int frameDelay = 1000 / FPS;

    while (running) {
        frameStart = renderer->getTicks();
        while (eventPort->pollEvent()) {
            if (eventPort->isQuitEvent()) {
                running = false;
            }
            player.handleEvent(eventPort); // Passa o adaptador de evento para o jogador
        }

        float deltaTime = (renderer->getTicks() - frameStart) / 1000.0f;

        // Atualiza o jogador e segmentos do chão
        player.update(deltaTime, groundSegments);

        renderer->draw(); // Desenha o fundo

        // Renderiza cada segmento do chão
        for (const auto& segment : groundSegments) {
            segment.render(renderer);
        }

        player.render(renderer); // Renderiza o jogador

        renderer->present(); 

        frameTime = renderer->getTicks() - frameStart;
        if (frameDelay > frameTime) {
            renderer->delay(frameDelay - frameTime);
        }
    }

    renderer->quit();
}
