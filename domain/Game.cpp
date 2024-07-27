#include "Game.h"
#include <iostream>

Game::Game(RendererPort *renderer,EventPort *eventPort,PageRenderPort *pageRenderPort)
    : renderer(renderer),
      eventPort(eventPort),
      pageRenderPort(pageRenderPort)
{
    // Inicializa objetos do jogo
    auto player = std::make_unique<Player>(Vector2D(375, 275), Vector2D(50, 50), Vector2D(0, 45.8f), 1.0f);
    auto groundSegment = std::make_unique<GroundSegment>(Vector2D(0, 580), Vector2D(800, 20), Vector2D(0, 0), 1000000000.0f);
    auto groundSegment2 = std::make_unique<GroundSegment>(Vector2D(0, 10), Vector2D(800, 20), Vector2D(0, 0), 10000000000.0f);
    gameObjects.push_back(std::move(player));
    gameObjects.push_back(std::move(groundSegment));
    gameObjects.push_back(std::move(groundSegment2));
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
                Vector2D const position = object->getPosition();
                std::cout << "Object Position: (" << position.x << ", " << position.y << ")" << std::endl;

                object->update(deltaTime, gameObjects);

                Vector2D const positionAfter = object->getPosition();
                std::cout << "Object Position After Update: (" << positionAfter.x << ", " << positionAfter.y << ")" << std::endl;
            }

            // Renderizar todos os objetos do jogo
            renderer->draw();

            for (const auto &object : gameObjects)
            {
                object->render(renderer);
            }

            pageRenderPort->present();

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
        pageRenderPort->quit();
    }
    catch (...)
    {
        std::cerr << "Erro desconhecido durante a execução do jogo." << std::endl;
        pageRenderPort->quit();
    }

    pageRenderPort->quit();
}
