#include <iostream>
#include "TelaInterface.h"
namespace models{
    namespace tela{
        class Tela: public TelaInterface {

        private:
        public:
            int getCima(){
                return cima;
            }
            int getBaixo(){
                return baixo;
            }
            int getDireita(){
                return direita;
            }
            void setCima(c){
                cima = c;
            }
            void setBaixo(b){
                baixo= b;
            }
            void setDireita(d){
                direita = d;
            }
        }
    }
}


