#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "uuid.h"

class GameObject {
public:
    bool suspended = false;
    std::string uuid = generate_uuid_v4();
    GameObject() {}
    virtual ~GameObject() {}
    
    bool tick(const bool&) {
        return true;
    }
    
    virtual void add_system_handlers() {}
    virtual void add_input_handlers() {}
};

#endif
