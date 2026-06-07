#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "exceptions.h"

class GameObject {
public:
    virtual void draw(SDL_Surface*);
    virtual void render(SDL_Window*);
    virtual ~GameObject() {};
};

class Stickman: public GameObject {
    const int WIDTH{403}, HEIGHT{363};
    int i{-1};
    SDL_Surface* bmp;
    SDL_Rect source{0,0,WIDTH,HEIGHT}, destination{0,0,WIDTH,HEIGHT};
public:
    Stickman();
    ~Stickman();
    void reset_frame();
    void next_frame(SDL_Surface* gSurface);
    void draw(SDL_Surface* gSurface) override;
    void render(SDL_Window* gSurface) override;
};

#endif
