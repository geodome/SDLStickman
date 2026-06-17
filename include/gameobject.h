#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdexcept>
#include "position.h"
#include "animation.h"
#include "controller.h"

class GameObject {
    Position* p;
    Animation* a;
    Controller* c;
public:
    GameObject() {}
    virtual ~GameObject() {}
    virtual Position* position() {
        if(p == nullptr) throw std::runtime_error("position is null pointer");
        return p;
    }
    virtual Animation* animation() {
        if(a == nullptr) throw std::runtime_error("animation is null pointer");
        return a;
    }
    virtual Controller* controller() {
        if(c == nullptr) throw std::runtime_error("controller is null pointer");
        return c;
    }
};
#endif
