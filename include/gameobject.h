#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdexcept>
#include "position.h"
#include "animation.h"
#include "controller.h"

class GameObject {
    Position* pos;
    Animation* anime;
    Controller* ctrl;
public:
    GameObject(double x, double y, double w, double h) {
        pos = new Position(x,y,w,h);
    }
    GameObject(Position* p, Animation* a, Controller * c): pos{p}, anime{a}, ctrl{c} {}
    virtual ~GameObject() {
        delete position();
    }
    void set_animation(Animation* a) {
        anime = a;
    }
    Animation* animation() {
        if(anime == nullptr) throw std::runtime_error{"no animation object was defined for this game object"};
        return anime;
    }
    Position* position() {
        return pos;
    }
    void set_controller(Controller* c) {
        ctrl = c;
    }
    Controller* controller() {
        if(ctrl == nullptr) throw std::runtime_error("no controller object was defined for this game object");
        return ctrl;
    }
};
#endif
