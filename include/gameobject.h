#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <SDL2/SDL.h>
#include "exceptions.h"

class GameObject {
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> handlers{};
public:
    GameObject() = default;
    virtual ~GameObject() = default;
    virtual void draw(SDL_Surface*) {};
    void add_handler(uint32_t, std::function<void(SDL_Event,bool&, bool&)>);
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> get_handlers();
};

std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> GameObject::get_handlers() {
    return handlers;
}

void GameObject::add_handler(uint32_t event_type, std::function<void(SDL_Event,bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}

class Stickman: public GameObject {
    const int WIDTH{400}, HEIGHT{366};
    int i{-1};
    SDL_Surface* bmp;
    SDL_Rect source{0,0,WIDTH,HEIGHT}, destination{0,0,WIDTH,HEIGHT};
public:
    Stickman();
    ~Stickman();
    void reset_frame();
    void next_frame();
    void draw(SDL_Surface* gSurface) override;
};

Stickman::Stickman():GameObject() {
    std::string file {"/Users/donaldsontan/projects/SDLStickman/SDLStickman/assets/stickman.bmp"};
    bmp = SDL_LoadBMP(file.c_str());
    if(bmp == nullptr) {
        auto msg = std::string{SDL_GetError()};
        throw SDL_Cannot_Load_Media(file, msg);
    }
    // toggles the animation on/off with a mouse click
    add_handler(SDL_MOUSEBUTTONDOWN, [] (SDL_Event e, bool& quit, bool& suspended) {
        suspended = !suspended;
    });
}

Stickman::~Stickman() {
    SDL_FreeSurface(bmp);
}

void Stickman::reset_frame() {
    i = -1;
    source = {0, 0, WIDTH, HEIGHT};
}

void Stickman::next_frame() {
    i = (i + 1) % 8;
    int x = i % 4;
    int y = i / 4;
    source.x = x*WIDTH;
    source.y = y*HEIGHT;
}

void Stickman::draw(SDL_Surface* gSurface) {
    next_frame();
    SDL_BlitSurface(bmp, &source, gSurface, &destination);
}

#endif


