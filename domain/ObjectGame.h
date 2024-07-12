#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include "Vector2D.h"
#include "Physics.h"
#include "Hitbox.h"
#include "VisualElement.h"
#include <vector>
#include <memory>

class ObjectGame : public VisualElement {
public:
    ObjectGame(Vector2D position, Vector2D size, Physics* physicsComponent);
    virtual ~ObjectGame() = default;

    virtual void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects);
    void applyPhysics(float deltaTime);
    bool checkCollision(const ObjectGame& other) const;
    void resolveCollision(ObjectGame& other);

    const Hitbox& getHitbox() const;

protected:
    Vector2D position;
    Vector2D size;
    Physics* physicsComponent;
    Hitbox hitbox;
};

#endif // GAMEOBJECT_HPP
