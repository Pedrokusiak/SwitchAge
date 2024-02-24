#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "Posicao.hpp"
#include <SDL.h>

namespace models {
    namespace inimigo { 
        class Inimigo : public Posicao {
        private: 
            int aceleracao = 0;
            SDL_Texture *textura; 
        public:
            int getAceleracao() {
                return aceleracao;
            }

            void setAceleracao(int aceleracaoSet) {
                aceleracao = aceleracaoSet;
            }

            SDL_Texture* getTextura() {
                return textura;
            }

            void setTextura(SDL_Texture *texturaSet) {
                textura = texturaSet;
            }
        };
    } 
}

#endif 