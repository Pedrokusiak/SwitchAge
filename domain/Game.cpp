#include "Game.h"
#include <adapters/SDL/SDLEventAdapter.h>
#include <adapters/SDL/SDLRendererAdapter.h>
#include <iostream>

Game::Game(RendererPort *renderer, EventPort *eventPort)
    : renderer(renderer),
      eventPort(eventPort) {
    // Inicializa objetos do jogo
    gameObjects.push_back(std::make_unique<GroundSegment>(Vector2D(0, 580), Vector2D(800, 20), Vector2D(0, 0), 0.0f)); // Chão com física estática
    gameObjects.push_back(std::make_unique<Player>(Vector2D(10, 500), Vector2D(50, 50), Vector2D(0, 9.8f), 1.0f)); // Jogador com física
    // Adicione mais objetos conforme necessário
}

void Game::run() {
    bool running = true;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;

    try {
        while (running) {
            frameStart = renderer->getTicks();

            while (eventPort->pollEvent()) {
                if (eventPort->isQuitEvent()) {
                    running = false;
                }

                // Atualizar eventos do jogador
                for (const auto& object : gameObjects) {
                    Player* player = dynamic_cast<Player*>(object.get());
                    if (player) {
                        player->handleEvent(eventPort);
                    }
                }
            }

            float deltaTime = (renderer->getTicks() - frameStart) / 1000.0f;

            // Atualizar todos os objetos do jogo
            for (const auto &object : gameObjects) {
                Vector2D position = object->getPosition();
                std::cout << "Object Position: (" << position.x << ", " << position.y << ")" << std::endl;

                object->update(deltaTime, gameObjects);

                Vector2D positionAfter = object->getPosition();
                std::cout << "Object Position After Update: (" << positionAfter.x << ", " << positionAfter.y << ")" << std::endl;
            }

            // Renderizar todos os objetos do jogo
            renderer->draw();

            for (const auto &object : gameObjects) {
                object->render(renderer);
            }

            renderer->present();

            frameTime = renderer->getTicks() - frameStart;
            if (frameDelay > frameTime) {
                renderer->delay(frameDelay - frameTime);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Erro durante a execução do jogo: " << e.what() << std::endl;
        renderer->quit();
    } catch (...) {
        std::cerr << "Erro desconhecido durante a execução do jogo." << std::endl;
        renderer->quit();
    }

    renderer->quit();
}
