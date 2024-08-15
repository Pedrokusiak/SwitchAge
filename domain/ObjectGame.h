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
    ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate);
    virtual ~ObjectGame() = default;

    virtual void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects);
    virtual void render(RendererPort* renderer) const = 0; // Método virtual puro

    void applyPhysics(float deltaTime);
    void handleHibernateCollision(ObjectGame& other, const Vector2D& overlap);
    void adjustForCollision(ObjectGame& other,const Vector2D& overlap);
    bool checkCollision(const ObjectGame& other) const;
    void resolveCollision(ObjectGame& other);

    const Hitbox& getHitbox() const { return hitbox; }
    Vector2D getPosition() const { return position; }
    Vector2D getSize() const { return size; }
   
    bool getHibernate() const { return hibernate; }


protected:

    bool hibernate;
    Vector2D size;
    Physics physicsComponent;
    Hitbox hitbox;
};

#endif // OBJECTGAME_H
