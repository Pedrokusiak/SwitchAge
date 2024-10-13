#include "Game.h"
#include "ports/RendererPort.h"
#include <SDL2/SDL.h>

#include <iostream>

Game::Game(RendererPort *renderer, EventPort *eventPort, TexturePort *texturePort, Camera camera)
    : renderer(renderer),
      eventPort(eventPort),
      texturePort(texturePort),
      camera(camera)
{

    auto playerTexture = texturePort->loadTexture("asserts/Personagem-image-removebg-preview.png");
    auto groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Terrain/Ground/Tilemap_Flat.png"); // Substitua pelo caminho correto

    // Configurando o jogador
    Vector2D playerPosition = {200, 200};
    Vector2D playerSize = {64, 64};
    Vector2D playerGravity = {0, 180.8};
    float playerMass = 1.0f;
    bool playerHibernate = false;

    std::unique_ptr<Player> player(new Player(playerPosition, playerSize, playerGravity, playerMass,
                                              playerHibernate, playerTexture, renderer, 64, 64, &mixerManager));


    // Cada linha tem 6 sprites
    // e temos 7
    player->addAnimation("idle", {2,3});

    player->addAnimation("walkLeft", {6,7});
    player->addAnimation("walkRight", {6, 7,8,9,2});
    player->addAnimation("jumpUp", {36,37});
    player->addAnimation("crouch", {15, 16});

    player->addAnimation("idleInverted", {36,37});
    player->addAnimation("walkLeftInverted", {39,40});
    player->addAnimation("walkRightInverted", {39,40});
    player->addAnimation("jumpUpInverted", {39,40});


    player->playAnimation("idle", true);

    gameObjects.push_back(std::move(player));

   
    // Configurações para os segmentos de chão
    const int segmentWidth = 200;
    const int segmentHeight = 32;
    const int floorY = 400;
    const int upperGroundY = 100; // Posição Y do chão superior

    // Criando o chão inferior
    std::unique_ptr<GroundSegment> lowerGround(new GroundSegment(
        Vector2D(0, floorY),
        Vector2D(800, segmentHeight), // Largura total da tela
        Vector2D(0, 0),
        1000.0f,
        true,
        groundTexture,
        renderer,
        32,
        32));
    
    gameObjects.push_back(std::move(lowerGround));

    // Criando o chão superior
    std::unique_ptr<GroundSegment> upperGround(new GroundSegment(
        Vector2D(0, upperGroundY),
        Vector2D(800, segmentHeight), // Largura total da tela
        Vector2D(0, 0),
        1000.0f,
        true,
        groundTexture,
        renderer,
        32,
        32));
    
    gameObjects.push_back(std::move(upperGround));

    // Criando plataformas adicionais (opcional)
    std::unique_ptr<GroundSegment> platform1(new GroundSegment(
        Vector2D(300, 250),
        Vector2D(200, segmentHeight),
        Vector2D(0, 0),
        1000.0f,
        true,
        groundTexture,
        renderer,
        32,
        32));

    
    gameObjects.push_back(std::move(platform1));        



   



    // mixerManager.loadMusic("background", "asserts/Sound/music.mp3");
    // mixerManager.playMusic("background", -1); // -1 para tocar em loop

    mixerManager.loadSound("jump", "asserts/Sound/jump-up.mp3");
}

void Game::run()
{
    bool running = true;
    Uint32 frameStart;
    const int FPS = 30;

    frameStart = renderer->getTicks();
    const int frameDelay = 1000 / FPS;
    Player *player = nullptr;

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
                    if (true)
                    {               // Verificar se a velocidade é negativa (movendo-se para a esquerda)
                        score += 1; // Aumenta a pontuação a cada frame em que o jogador se move para a esquerda
                    }
                    camera.centerOn(player->getPosition());
                }
                object->render(renderer, camera);
            }

            renderScore(score);
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

void Game::renderScore(int score)
{
    // Converte a pontuação em string para iterar sobre cada dígito
    std::string scoreStr = std::to_string(score);
    int startX = 10;      // Coordenada X inicial para desenhar o primeiro dígito
    int y = 10;           // Coordenada Y para todos os dígitos
    int digitWidth = 20;  // Largura de cada "dígito" (retângulo)
    int digitHeight = 30; // Altura de cada "dígito"

    for (char digitChar : scoreStr)
    {
        int digit = digitChar - '0'; // Converte o caractere para o valor inteiro correspondente (0-9)

        SDL_Color color;
        switch (digit)
        {
        case 0:
            color = {255, 255, 255, 255};
            break; // Branco para 0
        case 1:
            color = {0, 0, 255, 255};
            break; // Azul para 1
        case 2:
            color = {255, 0, 0, 255};
            break; // Vermelho para 2
        case 3:
            color = {0, 255, 0, 255};
            break; // Verde para 3
        case 4:
            color = {255, 255, 0, 255};
            break; // Amarelo para 4
        case 5:
            color = {0, 255, 255, 255};
            break; // Ciano para 5
        case 6:
            color = {255, 0, 255, 255};
            break; // Magenta para 6
        case 7:
            color = {128, 0, 128, 255};
            break; // Roxo para 7
        case 8:
            color = {255, 165, 0, 255};
            break; // Laranja para 8
        case 9:
            color = {128, 128, 128, 255};
            break; // Cinza para 9
        default:
            color = {255, 255, 255, 255};
            break; // Caso padrão
        }

        SDL_SetRenderDrawColor(renderer->getRenderer(), color.r, color.g, color.b, color.a);

        SDL_Rect digitRect = {startX, y, digitWidth, digitHeight};

        SDL_RenderFillRect(renderer->getRenderer(), &digitRect);

        startX += digitWidth + 5;

        std::cout << "Digito: " << digit << " sendo renderizado em (" << startX << ", " << y << ") com cor ("
                  << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ")" << std::endl;
    }
}