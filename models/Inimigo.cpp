
#include <iostream>
#include <SDL.h>
using namespace models;

class Inimigo : public Posicao{
    private: 
        int aceleracao = 0;
        SDL_Texture *texture;
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

        void setTextura(SDL_Texture texturaSet){
            textura = texturaSet;
        }

}