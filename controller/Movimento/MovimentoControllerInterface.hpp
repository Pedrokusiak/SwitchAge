#ifndef MOVIMENTACAO_CONTROLLER_H
#define MOVIMENTACAO_CONTROLLER_H

#include <SDL.h>
#include "Tela.h"

class MovimentacaoController {
private:
    Tela tela; 
public:
    void teclaParaCima(SDL_KeyboardEvent *event);
    void teclaParaBaixo(SDL_KeyboardEvent *event);
    void leEntrada(void);
};

#endif 