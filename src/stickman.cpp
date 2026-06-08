#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <format>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"

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
        auto x = std::to_string(e.motion.x);
        auto y = std::to_string(e.motion.y);
        std::cout << "mouse button down at (" << x << ", " << y << ")" << std::endl;
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


