#ifndef POSITION_H
#define POSITION_H

#include "vector2d.h"

namespace GameObjects {

class Position {
    Vector2D coord{0,0}, velocity{0,0}, acceleration{0,0};
public:
    Position(double x, double y): coord{x,y} {}
    ~Position() = default;
    Vector2D get_coord();
    Vector2D get_velocity();
    Vector2D get_acceleration();
    void update();
    Vector2D next_coord();
    void stop();
    void set_coord(double, double);
    void set_velocity(double, double);
    void set_acceleration(double, double);
};

}

#endif

