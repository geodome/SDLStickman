#include "vector2d.h"

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

Vector2D Vector2D::operator*(double k) {
    return {k*x, k*y};
}

Vector2D& Vector2D::operator*=(double k) {
    x *= k;
    y *= k;
    return *this;
}

Vector2D Vector2D::operator/(double k) {
    return {x/k, y/k};
}

Vector2D& Vector2D::operator/=(double k){
    x /= k;
    y /= k;
    return *this;
}

double Vector2D::magnitude() {
    return sqrtf(x*x + y*y);
}

Vector2D&  Vector2D::normalise() {
    *this /= magnitude();
    return *this;
}

Vector2D Vector2D::unit_vector() {
    return *this/magnitude();
}

Vector2D Vector2D::rotate(double a) {
    double x1 = x*cos(a) - y*sin(a);
    double y1 = x*sin(a) + y*cos(a);
    return {x1, y1};
}

Vector2D operator*(double k, Vector2D other) {
    return other*k;
}

std::ostream& operator<<(std::ostream& out, Vector2D other) {
    out << "(" << other.x << ", " << other.y << ")";
    return out;
}

bool Vector2D::operator==(const Vector2D& other) {
    return x == other.x && y == other.y;
}
