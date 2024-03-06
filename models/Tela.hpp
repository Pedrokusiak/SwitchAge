#ifndef TELA_HPP
#define TELA_HPP
#include <SDL.h>
#include "TelaInterface";

namespace models {
    namespace tela {
        class TelaSDL : public TelaInterface {
        private:    
            SDL_Renderer *render;
            SDL_Window *janela;
            Heroi heroi;
            Posicao posicaoHeroi;
            Posicao posicaoChao;
           
    public:
    int getCima() {
        return cima;
    }
    int getBaixo() {
        return baixo;
    }
    int getEsquerda() {
        return esquerda;
    }
    int getDireita() {
        return direita;
    }
    void setCima(int c) {
        cima = c;
    }
    void setBaixo(int b) {
        baixo = b;
    }
    void setEsquerda(int e) {
        esquerda = e;
    }
    void setDireita(int d) {
        direita = d;
    }

    Tela(SDL_Window* janela, SDL_Renderer* renderer) 
        : janela(janela), renderer(renderer) {}

    virtual void desenhar() override; 

        };
    }
    
}


#endif
