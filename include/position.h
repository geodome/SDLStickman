#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include "eventemitter.h"
#include "uuid.h"

class Position {
    std::vector<std::string> tick_handlers;
        
    void init() {
        add_tick_handler("tick_handler", [this] (bool) {
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
        init();
    }
    
    Position(double x, double y, double vx, double vy, double ax, double ay) {
        coord = {x,y};
        velocity = {vx, vy};
        acceleration = {ax, ay};
        init();
    }

    void add_tick_handler(std::string msg, std::function<bool(bool)> handler) {
        auto name = std::format("Position {} : {} ", uuid, msg);
        EventEmitter::system_tick->then(name, handler);
        tick_handlers.push_back(name);
    }

    ~Position() {
        for(auto& s: tick_handlers) {
            EventEmitter::system_tick->erase(s);
        }
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
