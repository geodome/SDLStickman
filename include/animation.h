#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdexcept>
#include <SDL2/SDL.h>
#include "position.h"

class Animation {
    uint32_t ticker, delay{1};
    bool suspended{false}, flip{false};
    Position* pos;
public:
    Animation(Position* p): pos{p} {}
    virtual ~Animation() {}
    virtual void load_media(SDL_Renderer* gRenderer) {}
    virtual void render(SDL_Renderer* gRenderer) {}
    virtual void update() {}
    uint32_t get_ticker() {
        return ticker;
    }
    void tick() {
        ticker = (ticker + 1) % delay;
    }
    bool to_update() {
        return ticker == 0;
    }
    void set_delay(uint32_t d) {
        delay = d;
    }
    void set_position(Position* p) {
        pos = p;
    }
    Position* position() {
        if(pos == nullptr) throw std::runtime_error("Position has not been defined for this Animation object");
        return pos;
    }
    bool is_suspended() {
        return suspended;
    }
    void suspend() {
        suspended = true;
    }
    void unsuspend() {
        suspended = false;
    }
    bool to_flip() {
        return flip;
    }
    void toggle_flip() {
        flip = !flip;
    }

};


#endif
