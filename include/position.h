#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include <string>
#include <functional>
#include "uuid.h"
#include "vector2d.h"
#include "eventemitter.h"

class Position {
    std::vector<std::string> tick_handlers;
    void init();
public:
    std::string uuid {generate_uuid_v4()};
    Vector2D coord, velocity, acceleration;
    Position();
    Position(double x, double y, double vx, double vy, double ax, double ay);
    void add_tick_handler(std::string msg, std::function<bool(bool)> handler);
    ~Position();
    void tick();
    Vector2D next();
};


#endif
