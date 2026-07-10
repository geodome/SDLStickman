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
    
    static const std::unique_ptr<Observable2<Viewport*, SDL_Renderer*>> system_render;
    static const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> render_background;
    static const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> render_midground;
    static const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> render_foreground;
    
    static const std::unique_ptr<Observable<Viewport*>> viewport_update;

    static const std::unique_ptr<Observable<SDL_Scancode>> key_up;
    static const std::unique_ptr<Observable<SDL_Scancode>> unfiltered_key_down;
    static const std::shared_ptr<Observable<SDL_Scancode>> key_down;
    
    static const std::unique_ptr<Observable<SDL_MouseButtonEvent>> mouse_up;
    static const std::unique_ptr<Observable<SDL_MouseButtonEvent>> mouse_down;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_single_click;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_double_click;
    static const std::shared_ptr<Observable<SDL_MouseButtonEvent>> mouse_right_click;
    
    static void handle_input(bool& quit) {
        // first handle input
        SDL_Event e;
        while(!quit && SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    EventEmitter::system_quit->notify(true);
                case SDL_KEYUP:
                    EventEmitter::key_up->notify(e.key.keysym.scancode);
                    break;
                case SDL_KEYDOWN:
                    EventEmitter::unfiltered_key_down->notify(e.key.keysym.scancode);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    EventEmitter::mouse_down->notify(e.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    EventEmitter::mouse_up->notify(e.button);
                    break;
            }
        }

    }
};

const SDL_Scancode EventEmitter::QUIT_KEY = SDL_SCANCODE_ESCAPE;

const SDL_Scancode EventEmitter::PAUSE_KEY = SDL_SCANCODE_P;

const std::unique_ptr<Observable<bool>> EventEmitter::system_quit = std::make_unique<Observable<bool>>("system_quit");

const std::unique_ptr<Observable<bool>> EventEmitter::system_pause = std::make_unique<Observable<bool>>("system_pause");

const std::unique_ptr<Observable<bool>> EventEmitter::system_tick = std::make_unique<Observable<bool>>("system_tick");

const std::unique_ptr<Observable<bool>> EventEmitter::system_update = std::make_unique<Observable<bool>>("system_update");

const std::unique_ptr<Observable2<Viewport*, SDL_Renderer*>> EventEmitter::system_render = std::make_unique<Observable2<Viewport*, SDL_Renderer*>>("system_render");

const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> EventEmitter::render_background = EventEmitter::system_render->then("render_background", [] (Viewport*, SDL_Renderer*) {
    return true;
});

const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> EventEmitter::render_midground = EventEmitter::render_background->then("render_midground", [] (Viewport*, SDL_Renderer*) {
    return true;
});

const std::shared_ptr<Observable2<Viewport*, SDL_Renderer*>> EventEmitter::render_foreground = EventEmitter::render_midground->then("render_foreground", [] (Viewport*, SDL_Renderer*) {
    return true;
});


const std::unique_ptr<Observable<SDL_Scancode>> EventEmitter::key_up = std::make_unique<Observable<SDL_Scancode>>("key_up");

const std::unique_ptr<Observable<SDL_Scancode>> EventEmitter::unfiltered_key_down = std::make_unique<Observable<SDL_Scancode>>("unfiltered_key_down");

const std::shared_ptr<Observable<SDL_Scancode>> EventEmitter::key_down = EventEmitter::unfiltered_key_down->then("unfiltered_key_down", [] (const SDL_Scancode& sc) {
    switch(sc) {
        case EventEmitter::PAUSE_KEY:
            std::cout << "Pause key pressed." << std::endl;
            EventEmitter::system_pause->notify(true);
            return false;
        case EventEmitter::QUIT_KEY:
            std::cout << "Quit key pressed." << std::endl;
            EventEmitter::system_quit->notify(true);
            return false;
        default:
            return true;
    }
});

const std::unique_ptr<Observable<SDL_MouseButtonEvent>> EventEmitter::mouse_up = std::make_unique<Observable<SDL_MouseButtonEvent>>("mouse_up");

const std::unique_ptr<Observable<SDL_MouseButtonEvent>> EventEmitter::mouse_down = std::make_unique<Observable<SDL_MouseButtonEvent>>("mouse_down");

const std::shared_ptr<Observable<SDL_MouseButtonEvent>> EventEmitter::mouse_single_click = EventEmitter::mouse_down->then("mouse_single_click", [] (const SDL_MouseButtonEvent& e) {
    return e.button == 0 && e.clicks == 1;
});

const std::shared_ptr<Observable<SDL_MouseButtonEvent>> EventEmitter::mouse_double_click = EventEmitter::mouse_down->then("mouse_double_click", [] (const SDL_MouseButtonEvent& e) {
    return e.button == 0 && e.clicks == 2;
});

const std::shared_ptr<Observable<SDL_MouseButtonEvent>> EventEmitter::mouse_right_click = EventEmitter::mouse_down->then("mouse_right_click", [] (const SDL_MouseButtonEvent& e) {
    return e.button == 2 && e.clicks == 1;
});

const std::unique_ptr<Observable<Viewport*>> EventEmitter::viewport_update = std::make_unique<Observable<Viewport*>>("viewport_update");

#endif
