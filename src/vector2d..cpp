#include "vector2d.h"
#include <iostream>
#include <stdexcept>

namespace System {
Vector2D Vector2D::operator+(Vector2D other) {
    return {x + other.x, y + other.y};
}

Vector2D& Vector2D::operator+=(Vector2D other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D Vector2D::operator-(Vector2D other) {
    return {x - other.x, y - other.y};
}

Vector2D& Vector2D::operator-=(Vector2D other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D Vector2D::operator*(double a) {
    return {x*a, y*a};
}

Vector2D& Vector2D::operator*=(double a) {
    x *= a;
    y *= a;
    return *this;
}

Vector2D Vector2D::operator/(double a) {
    if(a == 0) throw std::invalid_argument("division by zero error");
    return Vector2D(x/a, y/a);
}

Vector2D& Vector2D::operator/=(double a) {
    if(a == 0) throw std::invalid_argument("division by zero error");
    x /= a;
    y /= a;
    return *this;
}


std::ostream& operator<<(std::ostream& out, const Vector2D& other) {
    out << "(" << other.x << "," << other.y << ")";
    return out;
}


}
