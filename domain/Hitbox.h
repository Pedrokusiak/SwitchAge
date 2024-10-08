#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "Vector2D.h"

class Hitbox
{
public:
    Hitbox(Vector2D position, Vector2D size);
    void update(Vector2D position);
    bool intersects(const Hitbox &other) const;
    Vector2D getOverlap(const Hitbox &other) const;
    Vector2D getPosition() const
    {
        return position;
    }

    Vector2D getSize() const
    {
        return size;
    }


private:
    Vector2D position;
    Vector2D size;
};

#endif // HITBOX_HPP
