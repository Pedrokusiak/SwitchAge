
#include <iostream>
#include <SDL.h>
using namespace models;

class Heroi : public Posicao{
    private: 
        int aceleracao = 0;
        
    public:

        int getAceleracao(){
            return aceleracao;
        }

        void setAceleracao(int aceleracaoSet) {
            aceleracao = aceleracaoSet;
        }

        void setTextura(SDL_Texture texturaSet){
            textura = texturaSet;
        }

}