#include "viewport.h"



const int Viewport::LL = LOWERLIMIT*UNIT;
const int Viewport::UL = UPPERLIMIT*UNIT;
const int Viewport::WINDOW_WIDTH = WINDOW_COLS*UNIT;
const int Viewport::WINDOW_HEIGHT = WINDOW_ROWS*UNIT;

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::update_origin(const Vector2D coord) {
    auto [x, y] = coord;
    if(origin.x < x && x < origin.x + Viewport::LL)
        origin.x = fmax(0, x - Viewport::LL);
    else if(x > origin.x + Viewport::UL)
        origin.x = fmin(Viewport::WINDOW_WIDTH, x-Viewport::UL);
}

Vector2D Viewport::translate(const Vector2D coord) {
    auto [x,y] = coord;
    return {x - origin.x, y -  origin.y};
}

bool Viewport::is_visible(const BoundingBox& other) {
    auto s = BoundingBox(origin.x, origin.y, Viewport::WINDOW_WIDTH, Viewport::WINDOW_HEIGHT);
    return s.overlaps(other);
}
