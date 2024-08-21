#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"
#include "Camera.h"

class Player : public ObjectGame {
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hiberate);
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer, const Camera& camera) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override; // Adicione esta linha
};

#endif // PLAYER_HPP
