#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"
#include "Vector2D.h"
#include <memory>
#include <vector>
#include <adapters/SDL/SDLEventAdapter.h>

class Player : public ObjectGame {
public:
    Player(Vector2D position, Vector2D size, Physics* physicsComponent);
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override; 

private:
    Vector2D velocity;
    bool onGround;
};

#endif // PLAYER_HPP
