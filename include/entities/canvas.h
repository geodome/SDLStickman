#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>
#include "entity.h"
#include "sprite.h"
#include "system.h"
 
class Canvas: public Entity {
public:
    Canvas(uint8_t r, uint8_t g, uint8_t b, uint8_t a): Entity(EntityRole::CANVAS) {
        shape.add_render_handler("draw_red_canvas", [r, g, b, a] (Viewport* vp, SDL_Renderer* gRenderer) {
            SDL_SetRenderDrawColor(gRenderer,r,g,b,a);
            SDL_RenderFillRect(gRenderer,nullptr);
            std::cout << "rendering canvas\n";
            return true;
        });
    }
};
#endif
