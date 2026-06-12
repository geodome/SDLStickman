#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "exceptions.h"

namespace GameObjects {

class GameObject {
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> handlers{};
    
protected:
    uint32_t ticker{0}, delay;
public:
    GameObject(uint32_t delay_ticks=1);
    void tick();
    void reset_ticker();
    bool to_update();
    virtual ~GameObject() = default;
    virtual void update() {};
    virtual void render(SDL_Renderer*) {};
    void add_handler(uint32_t, std::function<void(SDL_Event,bool&, bool&)>);
    const std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> get_handlers();
};

}
#endif



