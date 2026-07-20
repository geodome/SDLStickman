#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include "eventemitter.h"
#include "uuid.h"
#include "viewport.h"

class Sprite {
    RenderOrder ro;
    std::string uuid;
    std::vector<std::string> tick_handlers;
    std::vector<std::string> update_handlers;
    std::vector<std::string> render_handlers;
public:

    Sprite(RenderOrder r);
    
    virtual void load_media(SDL_Renderer*) {};
    
    void add_tick_handler(const std::string& n, std::function<bool(const bool&)> handler);
    
    void add_update_handler(const std::string& n, std::function<bool(const bool&)> handler);
    
    void add_render_handler(const std::string& n, std::function<bool(Viewport*, SDL_Renderer*)> handler);

    virtual ~Sprite();
};

class Shape: public Sprite {
public:
    Shape(RenderOrder ro);
};

#endif
