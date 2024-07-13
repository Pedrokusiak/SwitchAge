#include "Game.h"
#include <adapters/SDL/SDLEventAdapter.h>
#include <adapters/SDL/SDLRendererAdapter.h>
#include <iostream>

Game::Game(RendererPort *renderer, EventPort *eventPort)
    : renderer(renderer),
      eventPort(eventPort),
      playerPhysics(Vector2D(0, 9.8f), 1.0f),
      groundPhysics(Vector2D(0, 0), 20), // Física estática para o chão
      player(Vector2D(50, 50), Vector2D(50, 50), &playerPhysics)
{
    // Inicializa objetos do jogo

    gameObjects.push_back(std::make_unique<Player>(Vector2D(50, 50), Vector2D(50, 50), &playerPhysics)); // Adicione o jogador
    gameObjects.push_back(std::make_unique<GroundSegment>(Vector2D(0, 50), Vector2D(0, 50), &groundPhysics));
    // Adicione mais objetos conforme necessário
}

void Game::run()
{
    bool running = true;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 45;
    const int frameDelay = 1000 / FPS;
    try
    {

        while (running)
        {
            frameStart = renderer->getTicks();

            while (eventPort->pollEvent())
            {
                if (eventPort->isQuitEvent())
                {
                    running = false;
                }
                player.handleEvent(eventPort);
            }

            float deltaTime = (renderer->getTicks() - frameStart) / 1000.0f;

            for (const auto &object : gameObjects)
            {

                object->update(deltaTime, gameObjects);
            }

            renderer->draw();

            for (const auto &object : gameObjects)
            {

                object->render(renderer);
            }

            renderer->present();

            frameTime = renderer->getTicks() - frameStart;
            if (frameDelay > frameTime)
            {
                renderer->delay(frameDelay - frameTime);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro durante a execução do jogo: " << e.what() << std::endl;
        renderer->quit();
    }
    catch (...)
    {
        std::cerr << "Erro desconhecido durante a execução do jogo." << std::endl;
        renderer->quit();
    }

    renderer->quit();
}
