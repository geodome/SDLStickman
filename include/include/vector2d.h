#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <stdexcept>

namespace GameObjects {

struct Vector2D {
    double x, y;
    Vector2D operator+(Vector2D other);
    Vector2D& operator+=(Vector2D other);
    Vector2D operator-(Vector2D other);
    Vector2D& operator-=(Vector2D other);
    Vector2D operator*(double a);
    Vector2D& operator*=(double a);
    Vector2D operator/(double a);
    Vector2D& operator/=(double a);
};

std::ostream& operator<<(std::ostream& out, const Vector2D& other);

}
#endif


