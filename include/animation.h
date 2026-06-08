#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <functional>
#include <vector>
#include <format>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"

class Animation {
    int WIDTH, HEIGHT;
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&,bool&)>>> handlers{};
    std::vector<GameObject*> gObjects;
public:
    static const int DELAY{50};
    Animation();
    ~Animation();
    void main_loop();
    void register_handler(uint32_t, std::function<void(SDL_Event, bool&, bool&)>);
    void handle_events(bool&, bool&);
    void tick();
    void update();
    void render();
    void add_game_object(GameObject*);
};

#endif
