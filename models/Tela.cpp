#include <iostream>
 using namespace models;

class Tela {

private:
    int cima;
    int baixo;
    int esquerda;
    int direita;
    SDL_Renderer *render;
    SDL_Window *janela;
public:
    int getCima(){
        return cima;
    }
    int getBaixo(){
        return baixo;
    }
    int getDireita(){
        return direita;
    }
    void setCima(c){
        cima = c;
    }
    void setBaixo(b){
        baixo= b;
    }
    void setDireita(d){
        direita = d;
    }
}
