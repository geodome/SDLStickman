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
    const int DELAY{100}, WIDTH{403}, HEIGHT{363};
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&,bool&)>>> handlers{};
    std::vector<GameObject*> gObjects;
public:
    Animation();
    ~Animation();
    void main_loop();
    void register_handler(uint32_t, std::function<void(SDL_Event, bool&, bool&)>);
    void handle_events(bool&, bool&);
    void draw();
    void render();
    void add_game_object(GameObject*);
};

Animation::Animation() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_Cannot_Init(SDL_GetError());
    }
    gWindow = SDL_CreateWindow("Stickman Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr) {
        throw SDL_Cannot_Init(SDL_GetError());
    }
    
    gSurface = SDL_GetWindowSurface(gWindow);
    if(gSurface == nullptr) {
        throw SDL_Cannot_Init(SDL_GetError());
    }
}

Animation::~Animation() {
    if(gSurface != nullptr) SDL_FreeSurface(gSurface);
    if(gWindow != nullptr)  SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void Animation::register_handler(uint32_t event_type, std::function<void(SDL_Event, bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}

void Animation::handle_events(bool& quit, bool& suspended) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        for(auto f: handlers[e.type]){
            f(e, quit, suspended);
            if(quit) break;
        }
        if(quit) break;
    }
}

void Animation::main_loop() {
    bool quit{false}, suspended{false};
    register_handler(SDL_QUIT, [] (SDL_Event e, bool& quit, bool& suspended) {
        quit = true;
        suspended = true;
    });
    while(!quit) {
        handle_events(quit, suspended);
        if(!suspended) {
            draw();
            render();
        }
        SDL_Delay(DELAY);
    }
}

void Animation::add_game_object(GameObject* g) {
    gObjects.push_back(g);
}

void Animation::draw() {
    for(auto obj: gObjects) {
        obj->draw(gSurface);
    }
}

void Animation::render() {
    SDL_UpdateWindowSurface(gWindow);
}

#endif
