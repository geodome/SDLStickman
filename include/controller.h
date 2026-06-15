#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include <vector>
#include <map>
#include <stdexcept>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

class Controller {
    std::map<SDL_Scancode, std::vector<std::function<void(bool&)>>> keyboard_handlers{};
    std::map<uint32_t, std::vector<std::function<void(SDL_Event, bool&)>>> mouse_handlers{};
    Position* pos;
    Animation* anime;
public:
    Controller(Position* p, Animation* a): pos{p}, anime{a} {}
    ~Controller() {}
    Position* position() {
        return pos;
    }
    Animation* animation() {
        return anime;
    }
    void add_keyboard_input(SDL_Scancode sc, std::function<void(bool&)> f) {
        keyboard_handlers[sc].push_back(f);
    }
    void add_mouse_input(SDL_EventType e, std::function<void(SDL_Event, bool&)> f) {
        switch(e) {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
                mouse_handlers[e].push_back(f);
                break;
            default:
                throw std::invalid_argument("Controller::add_mouse_input():: added unsupprted GUI event");
        }
        
    }
    void handle_keyboard_events(SDL_Event e, bool& quit) {
        if(e.type == SDL_KEYDOWN) {
            auto sc = e.key.keysym.scancode;
            for(auto f: keyboard_handlers[sc]) {
                f(quit);
                if(quit) break;
            }
        }
    }
    void handle_mouse_events(SDL_Event e, bool& quit) {
        switch(e.type) {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
                for(auto f: mouse_handlers[e.type]) {
                    f(e, quit);
                    if(quit) break;
                }
                break;
        }
    }
};
#endif
