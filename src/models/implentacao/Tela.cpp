#include <iostream>
#include "../TelaInterface.hpp"

        class Tela: public TelaInterface {

        private:
        	
        public:
           void desenhar() override {
           	
           }
            int getCima(){
                return cima;
            }
            int getBaixo(){
                return baixo;
            }
            int getDireita(){
                return direita;
            }
            void setCima(int c){
                this->cima = c;
            }
            void setBaixo(int b){
                this->baixo= b;
            }
            void setDireita(int d){
                this->direita = d;
            }
        };


