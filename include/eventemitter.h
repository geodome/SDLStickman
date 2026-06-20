#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include <functional>
#include <map>
#include <stdexcept>
#include <format>
#include <memory>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

template <typename T>
requires (!std::is_void_v<T>)
class Observable {
    std::string name;
    std::map<std::string, std::pair<std::shared_ptr<Observable>, std::function<bool(T)>>> subscribers{};
    void _notify(T& msg) {
        for(auto& [name, pair]: subscribers) {
            auto& [observer, to_notify] = pair;
            if(to_notify(msg)) observer->_notify(msg);
        }
    }
public:
    Observable(std::string n): name{n} {}
    ~Observable() {}
    std::shared_ptr<Observable> then(const std::string name, std::function<bool(T)> notifier) {
        if(subscribers.contains(name)) {
            auto msg = std::format("identifier {} is already used.", name);
            throw std::invalid_argument(msg);
        }
        auto observer = std::make_shared<Observable<T>>(name);
        subscribers[name] = {observer, notifier};
        return observer;
    }
    void notify(T msg) {
        _notify(msg);
    }
    bool erase(std::string id) {
        if(!subscribers.contains(id)) return false;
        subscribers.erase(id);
        std::cout << "Observer " << name << " removes " << id << std::endl;
        return true;
    }
};

class EventEmitter {
public:
    static const std::unique_ptr<Observable<bool>> system_quit, system_update, system_tick;
    static const std::unique_ptr<Observable<SDL_Renderer*>> system_render;
    static const std::unique_ptr<Observable<SDL_Scancode>> key_down;
    static const std::unique_ptr<Observable<SDL_Event>> mouse_button_down, mouse_button_up, mouse_motion;
    static void handle_input_events(bool& quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    EventEmitter::system_quit->notify(true);
                    break;
                case SDL_KEYDOWN:
                    EventEmitter::key_down->notify(e.key.keysym.scancode);
                    break;
                case SDL_MOUSEBUTTONUP:
                    EventEmitter::mouse_button_up->notify(e);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    EventEmitter::mouse_button_down->notify(e);
                    break;
                case SDL_MOUSEMOTION:
                    EventEmitter::mouse_motion->notify(e);
                    break;
            }
            if(quit) break;
        }
    }
};

const std::unique_ptr<Observable<bool>> EventEmitter::system_quit = std::make_unique<Observable<bool>>("system_quit");

const std::unique_ptr<Observable<bool>> EventEmitter::system_update = std::make_unique<Observable<bool>>("system_update");

const std::unique_ptr<Observable<SDL_Renderer*>> EventEmitter::system_render = std::make_unique<Observable<SDL_Renderer*>>("system_render");

const std::unique_ptr<Observable<bool>> EventEmitter::system_tick = std::make_unique<Observable<bool>>("system_tick");

const std::unique_ptr<Observable<SDL_Scancode>> EventEmitter::key_down = std::make_unique<Observable<SDL_Scancode>>("key_down");

const std::unique_ptr<Observable<SDL_Event>> EventEmitter::mouse_button_down = std::make_unique<Observable<SDL_Event>>("mouse_button_down");

const std::unique_ptr<Observable<SDL_Event>> EventEmitter::mouse_button_up = std::make_unique<Observable<SDL_Event>>("mouse_button_up");

const std::unique_ptr<Observable<SDL_Event>> EventEmitter::mouse_motion = std::make_unique<Observable<SDL_Event>>("mouse_motion");


#endif
