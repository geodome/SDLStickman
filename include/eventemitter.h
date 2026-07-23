#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include <memory>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>
#include "observable.h"
#include "vector2d.h"
#include "viewport.h"

enum RenderOrder {
    BACKGROUND,
    MIDGROUND,
    FOREGROUND
};

class EventEmitter {
public:
    static const SDL_Scancode QUIT_KEY, PAUSE_KEY;

    static const std::unique_ptr<Observable<bool>> system_quit;
    static const std::unique_ptr<Observable<bool>> system_pause;
    static const std::unique_ptr<Observable<bool>> system_tick;
    static const std::unique_ptr<Observable<bool>> system_update;
    
    static const std::unique_ptr<Observable2<Viewport*, SDL_Renderer*>> render_background;
    static const std::unique_ptr<Observable2<Viewport*, SDL_Renderer*>> render_midground;
    static const std::unique_ptr<Observable2<Viewport*, SDL_Renderer*>> render_foreground;
    
    static const std::unique_ptr<Observable<Viewport*>> viewport_update;

    static const std::unique_ptr<Observable<SDL_Scancode>> key_up;
    static const std::unique_ptr<Observable<SDL_Scancode>> unfiltered_key_down;
    static const std::shared_ptr<Observable<SDL_Scancode>> key_down;
    
    static const std::unique_ptr<Observable<SDL_MouseButtonEvent>> mouse_up;
    static const std::unique_ptr<Observable<SDL_MouseButtonEvent>> mouse_down;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_single_click;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_double_click;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_right_click;
    
    static void handle_input(bool& quit);
};

#endif
