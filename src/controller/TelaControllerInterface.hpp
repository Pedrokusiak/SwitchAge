#ifndef TELACONTROLLERINTERFACE_H
#define TELACONTROLLERINTERFACE_H

#include "../models/TelaInterface.hpp"

class TelaControllerInterface{
    private:
        TelaInterface* tela;
    public:
        virtual void processarEventos() = 0;
        void setTela(TelaInterface* tela){
            this->tela = tela;
        };
        TelaInterface* getTela(){
            return tela;
        }
    
};

#endif 
