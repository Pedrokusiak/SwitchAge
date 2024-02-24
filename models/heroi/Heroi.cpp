#include "Heroi.hpp"

namespace models {
    namespace heroi {
        int Heroi::getAceleracao() {
            return aceleracao;
        }

        void Heroi::setAceleracao(int aceleracaoSet) {
            aceleracao = aceleracaoSet;
        }

        void Heroi::setTextura(SDL_Texture *texturaSet) {
            textura = texturaSet;
        }
    } 
} 