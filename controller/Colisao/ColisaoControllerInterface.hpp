#ifndef COLISAO_CONTROLLER_H
#define COLISAO_CONTROLLER_H
#include "Tela.h"

class ColisaoController {
    private:
        Tela tela;
    public: 
        void estaTocando(Posicao posicao,Posicao posicao1);
}