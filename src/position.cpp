#include "position.h"

void Position::init() {
    add_tick_handler("tick_handler", [this] (bool) {
        this->tick();
        return true;
    });
}
    
Position::Position() {
    coord = {0,0};
    velocity = {0,0};
    acceleration = {0,0};
    init();
}
    
Position::Position(double x, double y, double vx, double vy, double ax, double ay) {
    coord = {x,y};
    velocity = {vx, vy};
    acceleration = {ax, ay};
    init();
}

void Position::add_tick_handler(std::string msg, std::function<bool(bool)> handler) {
    auto name = std::format("Position {} : {} ", uuid, msg);
    EventEmitter::system_tick->then(name, handler);
    tick_handlers.push_back(name);
}

Position::~Position() {
    for(auto& s: tick_handlers) {
        EventEmitter::system_tick->erase(s);
    }
}
    
void Position::tick() {
    coord += velocity;
    velocity += acceleration;
}
    
Vector2D Position::next() {
    return coord + velocity;
}
