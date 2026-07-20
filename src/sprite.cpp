#include "sprite.h"



Sprite::Sprite(RenderOrder r): ro{r}, uuid{generate_uuid_v4()} {}
    
void Sprite::add_tick_handler(const std::string& n, std::function<bool(const bool&)> handler) {
    auto name = std::format("Sprite {}: tick : {}", uuid, n);
    EventEmitter::system_tick->then(name, handler);
    tick_handlers.push_back(name);
}

void Sprite::add_update_handler(const std::string& n, std::function<bool(const bool&)> handler) {
    auto name = std::format("Sprite {} : update handler : ", uuid, n);
    EventEmitter::system_update->then(name, handler);
    update_handlers.push_back(name);
}

void Sprite::add_render_handler(const std::string& n, std::function<bool(Viewport*, SDL_Renderer*)> handler) {
    std::string name;
    switch(ro) {
        case RenderOrder::BACKGROUND:
            name = std::format("Sprite {}: Render Background: {}", uuid, n);
            EventEmitter::render_background->then(name, handler);
            break;
        case RenderOrder::MIDGROUND:
            name = std::format("Sprite {}: Render Midground: {}", uuid, n);
            EventEmitter::render_midground->then(name, handler);
            break;
        case RenderOrder::FOREGROUND:
            name = std::format("Sprite {}: Render Foreground: {}", uuid, n);
            EventEmitter::render_foreground->then(name, handler);
            break;
    }
    render_handlers.push_back(name);
}
    
Sprite::~Sprite() {
    for(auto& s: tick_handlers) {
        EventEmitter::system_update->erase(s);
    }
    for(auto& s: update_handlers) {
        EventEmitter::system_update->erase(s);
    }
    switch(ro) {
        case RenderOrder::BACKGROUND:
            for(auto& s: render_handlers) EventEmitter::render_background->erase(s);
            break;
        case RenderOrder::MIDGROUND:
            for(auto& s: render_handlers) EventEmitter::render_background->erase(s);
            break;
        case RenderOrder::FOREGROUND:
            for(auto& s: render_handlers) EventEmitter::render_background->erase(s);
            break;
    }
}

Shape::Shape(RenderOrder ro): Sprite(ro) {}
