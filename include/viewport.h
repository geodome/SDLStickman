#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SDL2/SDL_render.h>
#include "vector2d.h"
#include "boundingbox.h"
#include "global.h"

class Viewport {
    
public:
    Vector2D origin{0,0};
    static const int UNIT, LL, UL, WINDOW_WIDTH, WINDOW_HEIGHT;
    Viewport() {}
    ~Viewport() {}
    void update_origin(const Vector2D coord) {
        auto [x, y] = coord;
        if(origin.x < x && x < origin.x + Viewport::LL)
            origin.x = fmax(0, x - Viewport::LL);
        else if(x > origin.x + Viewport::UL)
            origin.x = fmin(Viewport::WINDOW_WIDTH, x-Viewport::UL);
    }
    Vector2D translate(const Vector2D& coord) {
        auto [x,y] = coord;
        return {x - origin.x, y -  origin.y};
    }
    bool is_visible(const BoundingBox& other) {
        auto s = BoundingBox(origin.x, origin.y, Viewport::WINDOW_WIDTH, Viewport::WINDOW_HEIGHT);
        return s.overlaps(other);
    }
};

const int Viewport::LL = Global::LL*Global::UNIT;
const int Viewport::UL = Global::UL*Global::UNIT;
const int Viewport::WINDOW_WIDTH = Global::COLS*Global::UNIT;
const int Viewport::WINDOW_HEIGHT = Global::ROWS*Global::UNIT;

#endif
