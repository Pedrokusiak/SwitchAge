#include <iostream>
 using namespace std;

class Posicao{
    private: 
        int posicaoX = 0
        int posicaoY = 0;
    public:

        int getPosicaoX() {
            return posicaoX;
        }

        int getPosicaoY() {
            return posicaoY;
        }

        void setPosicaoX(int posicaoXSet) {
            posicaoX  = posicaoXSet;
        }

         void setPosicaoY(int posicaoYSet) {
            posicaoY  = posicaoYSet;
        }

}