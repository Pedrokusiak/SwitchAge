
#include <iostream>
#include <SDL.h>
using namespace models;

class Heroi : public Posicao{
    private: 
        int aceleracao = 0;
        SDL_Texture *textura;
    public:

        int getAceleracao(){
            return this.aceleracao;
        }

        int getTextura(){
            return this.textura;
        }

        void setAceleracao(aceleracao) {
            this.aceleracao = aceleracao;
        }

        void setTextura(textura){
            this.textura = textura;
        }

}