#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

struct Vector2D {
    double x, y;
    Vector2D operator+(Vector2D other) {
        return Vector2D{x + other.x, y + other.y};
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
    Vector2D operator*(double k) {
        return {k*x, k*y};
    }
    Vector2D& operator*=(double k) {
        x *= k;
        y *= k;
        return *this;
    }
    Vector2D operator/(double k) {
        return {x/k, y/k};
    }
    Vector2D& operator/=(double k){
        x /= k;
        y /= k;
        return *this;
    }
};

Vector2D operator*(double k, Vector2D other) {
    return other*k;
}

std::ostream& operator<<(std::ostream& out, Vector2D other) {
    out << "(" << other.x << ", " << other.y << ")";
    return out;
}

#endif
