#include <SDL2/SDL.h>
#include "domain/Game.h"
#include <adapters/SDL/SDLRendererAdapter.h>
#include "PlayerPhysics.h" 

Game::Game(RendererPort *renderer)
    : renderer(renderer),
      playerPhysics(1, 10, -15),  // Inicializando PlayerPhysics com parâmetros adequados
      player(Position(50, 50), 50, 50, &playerPhysics)  // Passando a instância de PlayerPhysics
{}

void Game::run()
{
    bool running = true;
    SDL_Event event;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (running)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            player.handleEvent(event);
        }

        player.move();

        renderer->draw(); // Desenha o fundo

        player.render(renderer); // Renderiza o jogador

        SDL_RenderPresent(static_cast<SDLRendererAdapter*>(renderer)->getRenderer()); // Atualiza a tela com o renderizador SDL

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_Quit();
}
