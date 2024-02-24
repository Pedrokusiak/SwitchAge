#ifndef HEROI_HPP
#define HEROI_HPP

#include "Posicao.hpp" 
#include <SDL.h>

namespace models {
    namespace heroi { 

        class Heroi : public Posicao {
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

            void setTextura(SDL_Texture *texturaSet) {
                textura = texturaSet;
            }
        };

    } // namespace heroi
} // namespace models

#endif // HEROI_HPP
