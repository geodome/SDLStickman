#ifndef POSITION_H
#define POSITION_H

#include "vector2d.h"
#include "uuid.h"

class Position {
    std::string pos_tick;
    void add_tick_handler() {
        pos_tick = std::format("Position {} : tick", uuid);
        EventEmitter::system_tick->then(pos_tick, [this] (bool) {
            this->tick();
            return true;
        });
    }
public:
    std::string uuid {generate_uuid_v4()};
    Vector2D coord, velocity, acceleration;
    
    Position() {
        coord = {0,0};
        velocity = {0,0};
        acceleration = {0,0};
        add_tick_handler();
    }
    
    Position(double x, double y, double vx, double vy, double ax, double ay) {
        coord = {x,y};
        velocity = {vx, vy};
        acceleration = {ax, ay};
        add_tick_handler();
    }
    
    ~Position() {
        EventEmitter::system_tick->erase(pos_tick);
    }
    
    void tick() {
        coord += velocity;
        velocity += acceleration;
    }
    
    Vector2D next() {
        return coord + velocity;
    }
};

#endif
