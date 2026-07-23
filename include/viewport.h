#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SDL2/SDL_render.h>
#include "vector2d.h"
#include "boundingbox.h"
#include "global.h"

class Viewport {
    
public:
    Vector2D origin;
    static const int LL, UL, WINDOW_WIDTH, WINDOW_HEIGHT;
    Viewport();
    ~Viewport();
    void update_origin(const Vector2D coord);
    Vector2D translate(const Vector2D coord);
    bool is_visible(const BoundingBox& other);
};

#endif
