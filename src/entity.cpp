#include "entity.h"


RenderOrder Entity::get_render_order(EntityRole r) {
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

Entity::Entity(EntityRole r): uuid{generate_uuid_v4()}, role{r}, ro{get_render_order(r)}, shape{get_render_order(r)}, sprite{get_render_order(r)} {
    if(r == EntityRole::ALL) throw std::invalid_argument("EntityRole::ALL not valid for Entity");
    if(r == EntityRole::PLAYER) add_viewport_handler("viewport_update", [this] (Viewport* vp) {
        vp->update_origin(this->position.coord);
        std::cout << "update " << this->position.coord << " " << vp->origin << "\n";
        return true;
    });
}

void Entity::add_pause_handler(const std::string& n, std::function<bool(const bool&)> handler) {
    auto name = std::format("Entity {} : {}", uuid, n);
    EventEmitter::system_pause->then(name, handler);
    pause_handlers.push_back(name);
}

void Entity::add_viewport_handler(const std::string& n, std::function<bool(Viewport*)> handler) {
    auto name = std::format("Entity {} : {}", uuid, n);
    EventEmitter::viewport_update->then(name, handler);
    vp_handlers.push_back(name);
}

Entity::~Entity() {
    for(auto& s: pause_handlers) {
        EventEmitter::system_pause->erase(s);
    }
    for(auto& s: vp_handlers) {
        EventEmitter::viewport_update->erase(s);
    }
}

