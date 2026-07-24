#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

struct Vector2D {
    double x, y;
    Vector2D operator+(Vector2D other);
    
    Vector2D& operator+=(Vector2D other);
    
    Vector2D operator-(Vector2D other);
    
    Vector2D& operator-=(Vector2D other);
    
    Vector2D operator*(double k);
    
    Vector2D& operator*=(double k);
    
    Vector2D operator/(double k);
    
    Vector2D& operator/=(double k);
    
    bool operator==(const Vector2D& other) const;
    
    double magnitude();
    
    Vector2D&  normalise() ;
    
    Vector2D unit_vector() ;
    
    Vector2D rotate(double a);
};

Vector2D operator*(double k, Vector2D other);

std::ostream& operator<<(std::ostream& out, Vector2D other);



#endif

