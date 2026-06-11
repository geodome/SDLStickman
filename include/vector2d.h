#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <stdexcept>

struct Vector2D {
    double x, y;
    Vector2D operator+(Vector2D other) {
        return {x + other.x, y + other.y};
    }
    Vector2D& operator+=(Vector2D other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2D operator-(Vector2D other) {
        return {x - other.x, y - other.y};
    }
    Vector2D& operator-=(Vector2D other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2D operator*(double a) {
        return {x*a, y*a};
    }
    Vector2D& operator*=(double a) {
        x *= a;
        y *= a;
        return *this;
    }
    Vector2D operator/(double a) {
        if(a == 0) throw std::invalid_argument("division by zero error");
        return Vector2D(x/a, y/a);
    }
    Vector2D& operator/=(double a) {
        if(a == 0) throw std::invalid_argument("division by zero error");
        x /= a;
        y /= a;
        return *this;
    }
};

Vector2D operator*(double a, Vector2D other) {
    return other*a;
}

std::ostream& operator<<(std::ostream& out, const Vector2D& other) {
    out << "(" << other.x << "," << other.y << ")";
    return out;
}
#endif

