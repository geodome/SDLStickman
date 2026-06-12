#include <string>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "stickman.h"
#include "gameobject.h"

namespace GameObjects::Characters {

Stickman::Stickman(int x, int y, uint32_t delay_ticks):GameObject(delay_ticks) {
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
    SDL_DestroyTexture(bmp_texture);
}

void Stickman::reset_frame() {
    reset_ticker();
    i = 0;
    source = {0, 0, WIDTH, HEIGHT};
}

void Stickman::next_frame() {
    int x = i % 4;
    int y = i / 4;
    source.x = x*WIDTH;
    source.y = y*HEIGHT;
    i = (i + 1) % 8;
}

void Stickman::update() {
    if(!suspended && to_update()) {
        next_frame();
    }
}

void Stickman::render(SDL_Renderer* gRenderer) {
    if(bmp_texture == nullptr) load_media(gRenderer);
    SDL_RenderCopy(gRenderer, bmp_texture, &source, &destination);
}

void Stickman::toggle_animation() {
    suspended = !suspended;
}

void Stickman::load_media(SDL_Renderer* gRenderer) {
    std::string file {"/Users/donaldsontan/projects/mtd215/mtd215/assets/stickman.bmp"};
    SDL_Surface* bmp_surface = SDL_LoadBMP(file.c_str());
    if(bmp_surface == nullptr) {
        auto msg = std::string{SDL_GetError()};
        throw SDL_Cannot_Load_Media(file, msg);
    }
    bmp_texture = SDL_CreateTextureFromSurface(gRenderer, bmp_surface);
    SDL_FreeSurface(bmp_surface);
}
}
