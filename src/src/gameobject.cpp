#include <map>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "gameobject.h"

namespace GameObjects {

GameObject::GameObject(uint32_t delay_ticks): delay{delay_ticks} {}

void GameObject::tick() {
    ticker = (ticker + 1) % delay;
}

void GameObject::reset_ticker() {
    ticker = 0;
}

bool GameObject::to_update() {
    return ticker == 0;
}

const std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> GameObject::get_handlers() {
    return handlers;
}

void GameObject::add_handler(uint32_t event_type, std::function<void(SDL_Event,bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}

}
