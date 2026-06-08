#include <map>
#include <functional>
#include <vector>
#include <format>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"
#include "animation.h"

Animation::Animation() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_Cannot_Init(SDL_GetError());
    }
    gWindow = SDL_CreateWindow("Stickman Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr) {
        SDL_Quit();
        throw SDL_Cannot_Init(SDL_GetError());
    }
    
    gSurface = SDL_GetWindowSurface(gWindow);
    if(gSurface == nullptr) {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        throw SDL_Cannot_Init(SDL_GetError());
    }
    
    add_game_object(new Stickman(0,0,1));
    add_game_object(new Stickman(Stickman::WIDTH,0,2));
}

Animation::~Animation() {
    for(auto ptr: gObjects) {
        delete ptr;
    }
    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
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
            SDL_Delay(DELAY);
        }    }
}

void Animation::add_game_object(GameObject* g) {
    gObjects.push_back(g);
    for(auto& [event_type, handlers]: g->get_handlers()) {
        for(auto f: handlers) {
            register_handler(event_type, f);
        }
    }
}

void Animation::draw() {
    for(auto obj: gObjects) {
        obj->draw(gSurface);
    }
}

void Animation::render() {
    SDL_UpdateWindowSurface(gWindow);
}
