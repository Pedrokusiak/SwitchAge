#ifndef POSICAO_HPP
#define POSICAO_HPP

namespace models {
    namespace posicao {
class Posicao {
private:
    int posicaoX = 0;
    int posicaoY = 0;
public:
    int getPosicaoX();
    int getPosicaoY();
    void setPosicaoX(int posicaoXSet);
    void setPosicaoY(int posicaoYSet);
};
    }
}

#endif