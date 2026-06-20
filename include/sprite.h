#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <stdexcept>

class Sprite {
    uint32_t period{1};
    uint32_t ticker{0};
public:
    Sprite(uint32_t p): period{p} {
        if(p == 0) throw std::invalid_argument("period is at least 1 tick.");
    }
    void tick() {
        ticker = (ticker + 1) % period;
    }
    bool to_update() {
        return ticker == 0;
    }
};

#endif
