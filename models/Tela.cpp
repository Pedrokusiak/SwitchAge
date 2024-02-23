#include <iostream>

class Tela {

    SDL_Renderer *render;
    SDL_Window *janela;
private:
    int cima;
    int baixo;
    int esquerda;
    int direita;
public:
    int getCima(){
        return cima;
    }
    int getBaixo(){
        return baixo;
    }
    int getEsquerda(){
        return esquerda;
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
    void setEsquerda(e){
        esquerda = e;
    }
    void setDireita(d){
        direita = d;
    }
}
