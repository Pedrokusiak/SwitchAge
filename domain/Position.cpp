#include "Position.h"

Position::Position(int x, int y) : positionX(x), positionY(y) {}

int Position::getPositionX() {
    return positionX;
}

int Position::getPositionY() {
    return positionY;
}

void Position::setPositionX(int posicaoXSet) {
    positionX = posicaoXSet;
}

void Position::setPositionY(int posicaoYSet) {
    positionY = posicaoYSet;
}
