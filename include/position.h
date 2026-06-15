#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include "vector2d.h"

class Position {
    double width, height;
    Vector2D coord{}, velocity{}, acceleration{};
    bool suspended{false};
public:
    Position(double x, double y, double w, double h): coord{x,y}, width{w}, height{h} {}
    double get_width() {
        return width;
    }
    double get_height() {
        return height;
    }
    void set_coord(double x, double y) {
        coord = {x, y};
    }
    void set_velocity(double x, double y) {
        velocity = {x, y};
    }
    void set_acceleration(double x, double y) {
        acceleration = {x, y};
    }
    Vector2D get_coord() {
        return coord;
    }
    Vector2D get_velocity() {
        return velocity;
    }
    Vector2D get_acceleration() {
        return acceleration;
    }
    Vector2D next_coord() {
        return coord + velocity;
    }
    void next() {
        if(is_suspended()) return;
        coord += velocity;
        velocity += acceleration;
    }
    bool is_suspended() {
        return suspended;
    }
    void suspend() {
        suspended = true;
    }
    void unsuspend() {
        suspended = false;
    }
};

std::ostream& operator<<(std::ostream& out, Position p) {
    out << "Position[" << p.get_coord() << ", " << p.get_velocity() << ", " << p.get_acceleration() << "]";
    return out;
}
#endif
