#include "Game.h"
#include <adapters/SDL/SDLEventAdapter.h>
#include <adapters/SDL/SDLRendererAdapter.h>
#include <iostream>

Game::Game(RendererPort *renderer, EventPort *eventPort)
    : renderer(renderer),
      eventPort(eventPort)
{
    // Inicializa objetos do jogo
    auto player = std::make_unique<Player>(Vector2D(200, 550), Vector2D(50, 50), Vector2D(0, 20.0f), 1.0f);
    // auto groundSegment = std::make_unique<GroundSegment>(Vector2D(50, 500), Vector2D(1000, 500), Vector2D(0, 0), 1.0f);
    auto groundSegment = std::make_unique<Player>(Vector2D(50, 500), Vector2D(1000, 500), Vector2D(0, 0), 10.0f);

    gameObjects.push_back(std::move(player));
    gameObjects.push_back(std::move(groundSegment));
    // Adicione mais objetos conforme necessário
}

void Game::run()
{
    bool running = true;
    Uint32 frameStart;
    const int FPS = 30;
    frameStart = renderer->getTicks();
    const int frameDelay = 1000 / FPS;

    try
    {
        while (running)
        {
            const float deltaTime = (renderer->getTicks() - frameStart) / 1000.0f;
            frameStart = renderer->getTicks();

            while (eventPort->pollEvent())
            {
                if (eventPort->isQuitEvent())
                {
                    running = false;
                }

                // Atualizar eventos do jogador
                for (const auto &object : gameObjects)
                {
                    Player *player = dynamic_cast<Player *>(object.get());
                    if (player)
                    {
                        player->handleEvent(eventPort);
                    }
                }
            }

            

            // Atualizar todos os objetos do jogo
            for (const auto &object : gameObjects)
            {
                Vector2D position = object->getPosition();
                std::cout << "Object Position: (" << position.x << ", " << position.y << ")" << std::endl;

                object->update(deltaTime, gameObjects);

                Vector2D positionAfter = object->getPosition();
                std::cout << "Object Position After Update: (" << positionAfter.x << ", " << positionAfter.y << ")" << std::endl;
            }

            // Renderizar todos os objetos do jogo
            renderer->draw();

            for (const auto &object : gameObjects)
            {
                object->render(renderer);
            }

            renderer->present();

            const int frameTime =  renderer->getTicks() - frameStart;
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
