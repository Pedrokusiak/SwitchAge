
#include <iostream>
#include <SDL.h>
using namespace models;

class Inimigo : public Posicao{
    private: 
        int aceleracao = 0;
        SDL_Texture *texture;
    public:

        int getAceleracao(){
            return this.aceleracao;
        }

        int getNomeDoSprite(){
            return this.nomeDoSprite;
        }

        void setAceleracao(aceleracao) {
            this.aceleracao = aceleracao;
        }

        void setNomeDoSprite(nomeDoSprite){
            this.nomeDoSprite = nomeDoSprite;
        }

}