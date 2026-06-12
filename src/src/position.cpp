#include "vector2d.h"
#include "position.h"

namespace GameObjects {

Vector2D Position::get_coord() {
    return coord;
}

Vector2D Position::get_velocity() {
    return velocity;
}

Vector2D Position::get_acceleration() {
    return acceleration;
}

void Position::update() {
    coord += velocity;
    velocity += acceleration;
}

Vector2D Position::next_coord() {
    return coord + velocity;
}

void Position::set_coord(double x, double y) {
    coord.x = x;
    coord.y = y;
}

void Position::set_velocity(double x, double y) {
    velocity.x = x;
    velocity.y = y;
}

void Position::set_acceleration(double x, double y) {
    acceleration.x = x;
    acceleration.y = y;
}

void Position::stop() {
    velocity = {0,0};
    acceleration = {0,0};
}

}
