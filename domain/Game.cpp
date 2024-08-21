#include "Game.h"
#include <iostream>

Game::Game(RendererPort *renderer,EventPort *eventPort)
    : renderer(renderer),
      eventPort(eventPort),
      camera(0, 0, 800, 600)
{
    auto player = std::make_unique<Player>(Vector2D(100, 100), Vector2D(50, 50), Vector2D(0, 0.0f), 1.00f, false);
    auto groundSegment = std::make_unique<GroundSegment>(Vector2D(0, 580), Vector2D(800, 20), Vector2D(0, 0), 1000000000.0f, false);
    auto groundSegment2 = std::make_unique<GroundSegment>(Vector2D(0, 150), Vector2D(800, 20), Vector2D(0, 0), 10000000000.0f, false);
    auto groundSegment3 = std::make_unique<GroundSegment>(Vector2D(0, 75), Vector2D(800, 20), Vector2D(0, 0), 10000000000.0f, true);

    gameObjects.push_back(std::move(player));
    gameObjects.push_back(std::move(groundSegment));
    gameObjects.push_back(std::move(groundSegment2));
    gameObjects.push_back(std::move(groundSegment3));
}

void Game::run()
{
    bool running = true;
    Uint32 frameStart;
    const int FPS = 30;
    frameStart = renderer->getTicks();
    const int frameDelay = 1000 / FPS;
    Player* player = nullptr;



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
                for (const auto &object : gameObjects)
                {
                    player = dynamic_cast<Player *>(object.get());
                    if (player) {
                        
                        player->handleEvent(eventPort);
                        break;
                    }
                }
            }
            for (const auto &object : gameObjects)
            {
                object->update(deltaTime, gameObjects);
            }

             if (player) {
                camera.centerOn(player->getPosition());
            }

            renderer->draw();
            for (const auto &object : gameObjects)
            {
                
                object->render(renderer, camera);
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
