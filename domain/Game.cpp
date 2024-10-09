#include "Game.h"
#include "ports/RendererPort.h"
#include <iostream>

Game::Game(RendererPort *renderer,  EventPort *eventPort, TexturePort *texturePort, Camera camera)
    : renderer(renderer),
      eventPort(eventPort),
      texturePort(texturePort),
      camera(camera)
{

//     auto playerTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Resources/Trees/Tree.png");
//     auto groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Factions/Goblins/Buildings/Wood_House/Goblin_House.png"); // Substitua pelo caminho correto

//     // Configurando o jogador
//     Vector2D playerPosition = {200, 200};
//     Vector2D playerSize = {64, 64};
//     Vector2D playerGravity = {0, 90.8};
//     float playerMass = 10.0f;
//     bool playerHibernate = false;

//     std::unique_ptr<Player> player(new Player(playerPosition, playerSize, playerGravity, playerMass,
//                                               playerHibernate, playerTexture, renderer, 64, 64));

//     player->addAnimation("idle", {0, 1, 2, 3});
//     player->addAnimation("walkLeft", {4, 5, 6, 7});
//     player->addAnimation("walkRight", {8, 9, 10, 11});
//     player->addAnimation("jumpUp", {12, 13, 14});
//     player->addAnimation("crouch", {15, 16});
//     player->playAnimation("walkLeft", true);


  

//     gameObjects.push_back(std::move(player));

//     const int numGroundSegments = 5; // Número de segmentos de chão
//     const int segmentWidth = 160;     // Largura de cada segmento
//     const int segmentHeight = 64;     // Altura de cada segmento
//     const int floorY = 500;
//     const int ceilingY = 50;  // Posição Y do teto
         
//   for (int i = 0; i < numGroundSegments; ++i)
//     {
//         Vector2D groundPosition = {static_cast<float>(i * segmentWidth), static_cast<float>(floorY + (i % 2) * 30)};
//         Vector2D groundSize = {static_cast<float>(segmentWidth), static_cast<float>(segmentHeight)};

//         std::unique_ptr<GroundSegment> ground(new GroundSegment(
//             groundPosition,
//             groundSize,
//             Vector2D(0, 0),
//             1000.0f,
//             true,
//             groundTexture,
//             renderer,
//             128,
//             128
//         ));

//         gameObjects.push_back(std::move(ground));
//     }

//     // Criando segmentos de teto
//     for (int i = 0; i < numGroundSegments; ++i)
//     {
//         Vector2D ceilingPosition = {static_cast<float>(i * segmentWidth), static_cast<float>(ceilingY - (i % 2) * 30)};
//         Vector2D ceilingSize = {static_cast<float>(segmentWidth), static_cast<float>(segmentHeight)};

//         std::unique_ptr<GroundSegment> ceiling(new GroundSegment(
//             ceilingPosition,
//             ceilingSize,
//             Vector2D(0, 0),
//             1000.0f,
//             true,
//             groundTexture,
//             renderer,
//             64,
//             64
//         ));

//         gameObjects.push_back(std::move(ceiling));
//     }
//     auto playerTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Deco/18.png");
//     auto groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Deco/18.png");
//     auto player = std::make_unique<Player>(Vector2D(375, 100), Vector2D(50, 50), Vector2D(0, 0.0f), 1.00f, false, playerTexture, &mixerManager);
//     auto groundSegment = std::make_unique<GroundSegment>(Vector2D(0, 580), Vector2D(800, 20), Vector2D(0, 0), 1000000000.0f, false, groundTexture);

//     gameObjects.push_back(std::move(player));

//     const int numGroundSegments = 5; // Número de segmentos de chão
//     const int segmentWidth = 160;     // Largura de cada segmento
//     const int segmentHeight = 64;     // Altura de cada segmento
//     const int floorY = 500;
//     const int ceilingY = 50;  // Posição Y do teto
         
//   for (int i = 0; i < numGroundSegments; ++i)
//     {
//         Vector2D groundPosition = {static_cast<float>(i * segmentWidth), static_cast<float>(floorY + (i % 2) * 30)};
//         Vector2D groundSize = {static_cast<float>(segmentWidth), static_cast<float>(segmentHeight)};

//         std::unique_ptr<GroundSegment> ground(new GroundSegment(
//             groundPosition,
//             groundSize,
//             Vector2D(0, 0),
//             1000.0f,
//             true,
//             groundTexture,
//             renderer,
//             128,
//             128
//         ));

//         gameObjects.push_back(std::move(ground));
//     }

//     // Criando segmentos de teto
//     for (int i = 0; i < numGroundSegments; ++i)
//     {
//         Vector2D ceilingPosition = {static_cast<float>(i * segmentWidth), static_cast<float>(ceilingY - (i % 2) * 30)};
//         Vector2D ceilingSize = {static_cast<float>(segmentWidth), static_cast<float>(segmentHeight)};

//         std::unique_ptr<GroundSegment> ceiling(new GroundSegment(
//             ceilingPosition,
//             ceilingSize,
//             Vector2D(0, 0),
//             1000.0f,
//             true,
//             groundTexture,
//             renderer,
//             64,
//             64
//         ));

//         gameObjects.push_back(std::move(ceiling));
//     }

    // Carregar e reproduzir música de fundo
    mixerManager.loadMusic("background", "asserts/Sound/music.mp3");
    mixerManager.playMusic("background", -1); // -1 para tocar em loop

    mixerManager.loadSound("jump", "asserts/Sound/jump-up.mp3");
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

                        break;
                    }
                }
            }

            for (const auto &object : gameObjects)
            {
                object->update(deltaTime, gameObjects);
            }
            renderer->draw();
            for (const auto &object : gameObjects)
            {
                Player *player = dynamic_cast<Player *>(object.get());
                 if (player)
                    { 
                        camera.centerOn(player->getPosition());
                    }
                object->render(renderer, camera);
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

    // Parar música quando o jogo terminar
    mixerManager.stopMusic();
    renderer->quit();
}
