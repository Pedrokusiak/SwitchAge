#include "Game.h"
#include <iostream>

Game::Game(RendererPort *renderer, EventPort *eventPort, TexturePort *texturePort)
    : renderer(renderer),
      eventPort(eventPort),
      texturePort(texturePort)
{
    auto playerTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Deco/18.png");

    // Suponha que estas sejam as dimensões de cada quadro na sprite sheet
    int frameWidth = 64;  // largura do quadro
    int frameHeight = 64; // altura do quadro
    int numFrames = 4;    // número de quadros na animação de andar
    int startY = 0;       // Y da linha onde os quadros de andar começam na sprite sheet

    std::vector<Frame> walkingFrames;
    for (int i = 0; i < numFrames; i++)
    {
        Frame frame(i * frameWidth, startY, frameWidth, frameHeight);
        walkingFrames.push_back(frame);
    }
    Uint32 animationInterval = 250; // intervalo de atualização em milissegundos
    PlayerAnimation walkingAnimation(walkingFrames, animationInterval);
    auto player = std::make_unique<Player>(Vector2D(375, 100), Vector2D(50, 150), Vector2D(0, 0.0f), 1.00f, false, playerTexture, walkingAnimation);

    gameObjects.push_back(std::move(player));
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
                        std::cout << "Animation frame updated to: " << std::endl;
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
            const int frameTime = renderer->getTicks() - frameStart;
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
