#include <map>
#include <vector>
#include <functional>
#include <string>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"

std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> GameObject::get_handlers() {
    return handlers;
}

void GameObject::add_handler(uint32_t event_type, std::function<void(SDL_Event,bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}


