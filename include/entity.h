#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <functional>
#include "controller.h"
#include "position.h"
#include "sprite.h"
#include "boundingbox.h"
#include "uuid.h"
#include "viewport.h"

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <stdexcept>
#include "eventemitter.h"

enum EntityRole {
    PLAYER,
    NPC,
    OBSTACLES,
    CANVAS,
    ALL
};

class Entity {
    std::vector<std::string> pause_handlers;
    std::vector<std::string> vp_handlers;
    std::string uuid{generate_uuid_v4()};
    RenderOrder get_render_order(EntityRole r);
public:
    EntityRole role;
    RenderOrder ro;
    Position position;
    Shape shape;
    Sprite sprite;
    Controller controller;
    BoundingBox boundingbox;
    Entity(EntityRole r);
    virtual void load_media(SDL_Renderer*) {}
    virtual void setup_controller() {};
    virtual void setup_sprite() {};
    void add_pause_handler(const std::string& n, std::function<bool(const bool&)> handler);
    void add_viewport_handler(const std::string& n, std::function<bool(Viewport*)> handler);
    virtual ~Entity();
};



#endif
