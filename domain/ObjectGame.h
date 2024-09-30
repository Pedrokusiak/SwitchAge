#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include "Vector2D.h"
#include "Physics.h"
#include "Hitbox.h"
#include "VisualElement.h"
#include "Camera.h"
#include <vector>
#include <memory>
#include "Animation.h"
class ObjectGame : public VisualElement {
public:
   ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
               std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight);
    virtual ~ObjectGame() override = default;

    virtual void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects);
    virtual void render(RendererPort* renderer, const Camera& camera) const = 0;

    void applyPhysics(float deltaTime);
    void handleHibernateCollision(ObjectGame& other, const Vector2D& overlap);
    void adjustForCollision(ObjectGame& other,const Vector2D& overlap);
    bool checkCollision(const ObjectGame& other) const;
    void resolveCollision(ObjectGame& other);

    const Hitbox& getHitbox() const { return hitbox; }
    Vector2D getSize() const { return size; }
   
    bool getHibernate() const { return hibernate; }


protected:

    bool hibernate;
    Vector2D size;
    Physics physicsComponent;
    Hitbox hitbox;
    std::unique_ptr<Animation> animation; 
};

#endif // OBJECTGAME_H
