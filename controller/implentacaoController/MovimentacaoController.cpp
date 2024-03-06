#include "MovimentacaoController.h"

void MovimentacaoController::teclaParaCima(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            tela.setCima(1);
        }
        else if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            tela.setBaixo(1); 
        }
        else if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            tela.setDireita(1); 
        }
    }
}

void MovimentacaoController::teclaParaBaixo(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            tela.setCima(1); 
        }
        else if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            tela.setBaixo(1);
        }
        else if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            tela.setDireita(1); 
        }
    }
}

void MovimentacaoController::leEntrada() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                teclaParaBaixo(&event.key);
                break;
            case SDL_KEYUP:
                teclaParaCima(&event.key);
                break;
            default:
                break;
        }
    }
}
