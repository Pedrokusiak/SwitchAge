#ifndef TEXTURA_HPP
#define TEXTURA_HPP

#include "Posicao.hpp" 
#include <SDL.h> 

namespace models {
    class Textura {
    private:
        SDL_Texture *textura; 
    public:
        void setTextura(SDL_Texture *texturaSet);
        SDL_Texture* getTextura();
    };
} 

#endif 
