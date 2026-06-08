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
    const std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> get_handlers();
};

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

#endif


