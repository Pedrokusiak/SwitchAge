#include "Game.h"
#include "ports/RendererPort.h"
#include <SDL2/SDL.h>
#include <iostream>

Game::Game(RendererPort* renderer, EventPort* eventPort, TexturePort* texturePort, Camera camera)
    : renderer(renderer),
      eventPort(eventPort),
      texturePort(texturePort),
      camera(camera)
{
    // Carregar texturas necessárias
    auto playerTexture = texturePort->loadTexture("asserts/Personagem-image-removebg-preview.png");
    auto groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Terrain/Ground/Tilemap_Flat.png");

    // Configurando o jogador
    Vector2D playerPosition = {50, 150};
    Vector2D playerSize = {64, 64};
    Vector2D playerGravity = {0, 180.8};
    float playerMass = 1.0f;
    bool playerHibernate = false;

    std::unique_ptr<Player> player(new Player(playerPosition, playerSize, playerGravity, playerMass,
                                            playerHibernate, playerTexture, renderer, 64, 64, &mixerManager));

    // Configurar animações do jogador
    player->addAnimation("idle", {2,3});
    player->addAnimation("walkRight", {7,8,9});
    player->addAnimation("jumpUp", {36,37,38,40});
    player->addAnimation("crouch", {15, 16});
    player->addAnimation("idleInverted", {36,37});
    player->addAnimation("walkLeftInverted", {39,40});
    player->addAnimation("walkRightInverted", {39,40});
    player->addAnimation("jumpUpInverted", {39,40});

    player->playAnimation("walkRight", true);

    // Adicionar jogador aos objetos do jogo
    gameObjects.push_back(std::move(player));

    // Inicializar o TerrainManager
    const int TILE_SIZE = 32;
    terrainManager = std::make_unique<TerrainManager>(renderer, texturePort, TILE_SIZE);
    
    // Configurar o nível
    const int LEVEL_WIDTH = 100;   // Largura do nível em tiles
    const int LEVEL_HEIGHT = 25;   // Altura do nível em tiles
    
    // Inicializar o nível (isso vai usar a vectorListTerrain internamente)
    terrainManager->initializeLevel(LEVEL_WIDTH, LEVEL_HEIGHT);

    // Adicionar os segmentos gerados aos gameObjects
    const auto& segments = terrainManager->getSegments();
    for (const auto& segment : segments) {
        auto newSegment = std::make_unique<GroundSegment>(
            segment->getPosition(),                // position
            Vector2D(segment->getWidth(), segment->getHeight()),  // size
            Vector2D(0, 0),                       // gravity
            1000.0f,                              // mass
            true,                                 // hibernate
            groundTexture,                        // texture
            renderer,                             // renderer
            TILE_SIZE,                            // frameWidth
            TILE_SIZE                             // frameHeight
        );
        gameObjects.push_back(std::move(newSegment));
    }

    // Carregar sons
    mixerManager.loadSound("jump", "asserts/Sound/jump-up.mp3");
}
   

void Game::run()
{
    bool running = true;
    Uint32 frameStart;
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;

    try
    {
        while (running)
        {
            frameStart = renderer->getTicks();
            const float deltaTime = 1.0f / FPS;

            renderer->draw();

            while (eventPort->pollEvent())
            {
                if (eventPort->isQuitEvent())
                {
                    running = false;
                }
                
                for (const auto& object : gameObjects)
                {
                    if (auto player = dynamic_cast<Player*>(object.get()))
                    {
                        player->handleEvent(eventPort);
                        break;
                    }
                }
            }

            // Atualizar objetos
            for (const auto& object : gameObjects)
            {
                object->update(deltaTime, gameObjects);
            }

            // Atualizar câmera
            for (const auto& object : gameObjects)
            {
                if (auto player = dynamic_cast<Player*>(object.get()))
                {
                    camera.centerOn(player->getPosition());
                    break;
                }
            }

            // Renderizar objetos
            for (const auto& object : gameObjects)
            {
                object->render(renderer, camera);
            }

            // Renderizar pontuação
            // renderScore(score);

            renderer->present();

            const int frameTime = renderer->getTicks() - frameStart;
            if (frameDelay > frameTime)
            {
                renderer->delay(frameDelay - frameTime);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro durante a execução do jogo: " << e.what() << std::endl;
        renderer->quit();
    }
    catch (...)
    {
        std::cerr << "Erro desconhecido durante a execução do jogo." << std::endl;
        renderer->quit();
    }

    mixerManager.stopMusic();
    renderer->quit();
}