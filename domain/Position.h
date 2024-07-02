#ifndef POSICAO_HPP
#define POSICAO_HPP

class Position
{
private:
    int positionX = 0;
    int positionY = 0;

public:
    int getPositionX();
    int getPositionY();
    void setPositionX(int posicaoXSet);
    void setPositionY(int posicaoYSet);

    Position(int positionX,int positionY);
};

#endif