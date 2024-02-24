#ifndef TELA_HPP
#define TELA_HPP
#include <SDL.h>
namespace models {
    namespace tela {
        class Tela {
        private:    
            SDL_Renderer *render;
            SDL_Window *janela;
            int cima;
            int baixo;
            int esquerda;
            int direita;
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
};
    }
    
}


#endif
