#ifndef STICKMAN_H
#define STICKMAN_H

#include <SDL2/SDL.h>
#include "gameobject.h"

namespace Character {

class Stickman: public System::GameObject {
    uint32_t i{0};
    SDL_Texture* bmp_texture;
    SDL_Rect source{0,0,WIDTH,HEIGHT}, destination{0,0,WIDTH,HEIGHT};
    bool suspended{false};
public:
    static const int WIDTH{400}, HEIGHT{366};
    Stickman(int x, int y, uint32_t delay_ticks);
    ~Stickman();
    void reset_frame();
    void next_frame();
    void update() override;
    void render(SDL_Renderer*) override;
    void toggle_animation();
    void load_media(SDL_Renderer*);
};

}
#endif
