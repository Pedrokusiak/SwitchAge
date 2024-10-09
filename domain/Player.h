#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"
#include "Camera.h"
#include <SDL2/SDL.h>

class Player : public ObjectGame {
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate);
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer, const Camera& camera) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override;

private:
    float lastGravityFlip;
    Vector2D calculateCollisionNormal(const ObjectGame& other) const;
    void handleGroundedState(const Vector2D& normal);
};

#endif // PLAYER_HPP