
#include <iostream>
#include <SDL.h>
using namespace models;

class Heroi : public Posicao{
    private: 
        int aceleracao = 0;
        SDL_Texture *textura;
    public:

        int getAceleracao(){
            return aceleracao;
        }

        int getTextura(){
            return textura;
        }

        void setAceleracao(int aceleracaoSet) {
            aceleracao = aceleracaoSet;
        }

        void setTextura(SDL_Texture texturaSet){
            textura = texturaSet;
        }

}