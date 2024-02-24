
#include <iostream>
#include <SDL.h>
using namespace models.Inimigo;

class Inimigo : public Posicao{
    private: 
        int aceleracao = 0;
    public:

        int getAceleracao(){
            return aceleracao;
        }

        SDL_Texture getTextura(){
            return textura;
        }

        void setAceleracao(int aceleracaoSet) {
            aceleracao = aceleracaoSet;
        }

    

}