#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "eventemitter.h"
#include "uuid.h"

class Controller {
    std::string uuid;
    std::vector<std::string> ku_handlers;
    std::vector<std::string> kd_handlers;
    std::vector<std::string> mouse_1click;
    std::vector<std::string> mouse_2click;
    std::vector<std::string> mouse_rclick;
public:
    Controller(): uuid{generate_uuid_v4()} {}
    
    virtual ~Controller() {
        for(auto s: ku_handlers) {
            EventEmitter::key_down->erase(s);
        }
        for(auto s: kd_handlers) {
            EventEmitter::key_down->erase(s);
        }
        for(auto s: mouse_1click) {
            EventEmitter::mouse_single_click->erase(s);
        }
        for(auto s: mouse_2click) {
            EventEmitter::mouse_double_click->erase(s);
        }
        for(auto s: mouse_rclick) {
            EventEmitter::mouse_right_click->erase(s);
        }
    }
    
    void system_quit() {
        EventEmitter::system_quit->notify(true);
    }
    
    void add_keyup_handler(const std::string& n, std::function<bool(SDL_Scancode)> handler) {
        auto name = std::format("Controller {} : {}", uuid, n);
        EventEmitter::key_up->then(name, handler);
        ku_handlers.push_back(name);
    }

    void add_keydown_handler(const std::string& n, std::function<bool(SDL_Scancode)> handler) {
        auto name = std::format("Controller {} : {}", uuid, n);
        EventEmitter::key_down->then(name, handler);
        kd_handlers.push_back(name);
    }
    
    void add_single_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler) {
        auto name = std::format("Controller {} : {}", uuid, n);
        EventEmitter::mouse_single_click->then(name, handler);
        mouse_1click.push_back(n);
    }
    
    void add_double_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler) {
        auto name = std::format("Controller {} : {}", uuid, n);
        EventEmitter::mouse_double_click->then(name, handler);
        mouse_2click.push_back(n);
    }
    
    void add_right_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler) {
        auto name = std::format("Controller {} : {}", uuid, n);
        EventEmitter::mouse_right_click->then(name, handler);
        mouse_rclick.push_back(n);
    }

};

#endif
