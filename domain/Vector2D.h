#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>  // Adicionado para usar std::sqrt

class Vector2D {
public:
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

      Vector2D operator-() const {
        return Vector2D(-x, -y);
    }

  

    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2D normalize() const {
        float mag = magnitude();
        if (mag > 0) {
            return Vector2D(x / mag, y / mag);
        }
        return *this;
    }

    float dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    static Vector2D zero() {
        return Vector2D(0, 0);
    }

    float magnitude() const {
    return std::sqrt(x * x + y * y);
    }
};

#endif // VECTOR2D_HPP
