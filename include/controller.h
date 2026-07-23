#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <functional>
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_events.h"
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
    Controller();
    
    virtual ~Controller();
    
    void system_quit();
    
    void toggle_pause();
    
    void add_keyup_handler(const std::string& n, std::function<bool(SDL_Scancode)> handler);

    void add_keydown_handler(const std::string& n, std::function<bool(SDL_Scancode)> handler);
    
    void add_single_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler);
    
    void add_double_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler);
    
    void add_right_click_handler(const std::string n, std::function<bool(SDL_MouseButtonEvent)> handler);

};


#endif
