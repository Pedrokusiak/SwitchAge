#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"

class Player : public ObjectGame {
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass);
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer) const override;

private:
    bool onGround;  // Adiciona o estado onGround somente para o player
};

#endif // PLAYER_HPP
