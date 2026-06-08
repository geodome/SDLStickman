#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <format>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"

Stickman::Stickman(int x, int y, int delay_ticks):GameObject() {
    std::string file {"/Users/donaldsontan/projects/SDLStickman/SDLStickman/assets/stickman.bmp"};
    bmp = SDL_LoadBMP(file.c_str());
    if(bmp == nullptr) {
        auto msg = std::string{SDL_GetError()};
        throw SDL_Cannot_Load_Media(file, msg);
    }
    // toggles the animation on/off with a mouse click
    add_handler(SDL_MOUSEBUTTONDOWN, [x,y, this] (SDL_Event e, bool& quit, bool& suspended) {
        auto dx = e.button.x - x;
        auto dy = e.button.y - y;
        if(dx > 0 && dx < WIDTH && dy > 0 && dy < HEIGHT) this->toggle_animation();
    });
    destination.x = x;
    destination.y = y;
    delay = delay_ticks;
}

Stickman::~Stickman() {
    SDL_FreeSurface(bmp);
}

void Stickman::reset_frame() {
    i = -1;
    source = {0, 0, WIDTH, HEIGHT};
}

void Stickman::next_frame() {
    if (!suspended) {
        i = (i + 1) % 8;
        int x = i % 4;
        int y = i / 4;
        source.x = x*WIDTH;
        source.y = y*HEIGHT;
    }
}

void Stickman::draw(SDL_Surface* gSurface) {
    if(!suspended) {
        ticks = (ticks + 1) % delay;
        if(ticks == 0) {
            next_frame();
            SDL_BlitSurface(bmp, &source, gSurface, &destination);
        }
    }
}

void Stickman::toggle_animation() {
    suspended = !suspended;
}
