#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <SDL2/SDL.h>
#include "exceptions.h"

class GameObject {
public:
    GameObject() = default;
    virtual void draw(SDL_Surface*) {};
    virtual ~GameObject() = default;
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

