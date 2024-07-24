#ifndef OBJECTGAMESTATIC_H
#define OBJECTGAMESTATIC_H

#include <vector>
#include <memory>
#include "ObjectGame.h"

class ObjectGameStatic : public ObjectGame {
public:
    ObjectGameStatic(Vector2D position, Vector2D size, Vector2D gravity, float mass);
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override;
};

#endif // OBJECTGAMESTATIC_H
