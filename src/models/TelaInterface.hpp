#ifndef TELAINTERFACE_H
#define TELAINTERFACE_H


class TelaInterface {
    public:
        virtual ~TelaInterface() {}
        virtual void desenhar() = 0;
    private:
        int cima;
        int baixo;
        int esquerda;
        int direita;
    }
#endif 
