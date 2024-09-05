#include "Game.h"
#include <iostream>

Game::Game(RendererPort *renderer,EventPort *eventPort, TexturePort *texturePort)
    : renderer(renderer),
      eventPort(eventPort),
      texturePort(texturePort)
{
    auto playerTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Deco/18.png");
    auto groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Deco");

    auto player = std::make_unique<Player>(Vector2D(375, 100), Vector2D(50, 150), Vector2D(0, 0.0f), 1.00f, false, playerTexture);
    auto groundSegment = std::make_unique<GroundSegment>(Vector2D(0, 580), Vector2D(800, 20), Vector2D(0, 0), 1000000000.0f, false, groundTexture);

    gameObjects.push_back(std::move(player));
    gameObjects.push_back(std::move(groundSegment));
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
            renderer->draw();
            while (eventPort->pollEvent())
            {
                if (eventPort->isQuitEvent())
                {
                    running = false;
                }
                for (const auto &object : gameObjects)
                {
                    
                    Player *player = dynamic_cast<Player *>(object.get());
                    if (player)
                    { 
                        player->handleEvent(eventPort);
                    }
                }
            }
       

            for (const auto &object : gameObjects)
            {
                object->update(deltaTime, gameObjects);
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
