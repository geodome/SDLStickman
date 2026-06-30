#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <stdexcept>
#include "controller.h"
#include "position.h"
#include "sprite.h"
#include "boundingbox.h"

enum EntityRole {
    PLAYER,
    NPC,
    OBSTACLES,
    CANVAS,
    ALL
};


class Entity {
    RenderOrder get_render_order(EntityRole r) {
        switch(r) {
            case EntityRole::ALL:
            case EntityRole::PLAYER:
                return RenderOrder::FOREGROUND;
            case EntityRole::NPC:
            case EntityRole::OBSTACLES:
                return RenderOrder::MIDGROUND;
            case EntityRole::CANVAS:
                return RenderOrder::BACKGROUND;
        }
    }
public:
    EntityRole role;
    RenderOrder ro;
    Position position;
    Shape shape;
    Sprite sprite;
    Controller controller;
    BoundingBox boundingbox;
    Entity(EntityRole r): role{r}, ro{get_render_order(r)}, shape{get_render_order(r)}, sprite{get_render_order(r)} {
        if(r == EntityRole::ALL) throw std::invalid_argument("EntityRole::ALL not valid for Entity");
    }
    virtual void load_media(SDL_Renderer*) {}
    virtual void setup_controller() {};
    virtual void setup_sprite() {};
};


#endif
