#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"
#include "system.h"

System::System(): WIDTH{2*Stickman::WIDTH}, HEIGHT{2*Stickman::HEIGHT} {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_Cannot_Init(SDL_GetError());
    }
    gWindow = SDL_CreateWindow("Stickman Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr) {
        SDL_Quit();
        throw SDL_Cannot_Init(SDL_GetError());
    }
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == nullptr) {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        throw SDL_Cannot_Init(SDL_GetError());
    }
    
    add_game_object(new Stickman(0,0,1));
    add_game_object(new Stickman(Stickman::WIDTH,0,2));
    add_game_object(new Stickman(0,Stickman::HEIGHT,3));
    add_game_object(new Stickman(Stickman::WIDTH,Stickman::HEIGHT, 4));

}

System::~System() {
    for(auto ptr: gObjects) {
        delete ptr;
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void System::register_handler(uint32_t event_type, std::function<void(SDL_Event, bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}

void System::handle_events(bool& quit, bool& suspended) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        for(auto f: handlers[e.type]){
            f(e, quit, suspended);
            if(quit) break;
        }
        if(quit) break;
    }
}

void System::main_loop() {
    bool quit{false}, suspended{false};
    register_handler(SDL_QUIT, [] (SDL_Event e, bool& quit, bool& suspended) {
        quit = true;
        suspended = true;
    });
    while(!quit) {
        handle_events(quit, suspended);
        if(!suspended) {
            update();
            render();
            tick();
            SDL_Delay(DELAY);
        }
    }
}

void System::add_game_object(GameObject* g) {
    gObjects.push_back(g);
    for(auto& [event_type, handlers]: g->get_handlers()) {
        for(auto f: handlers) {
            register_handler(event_type, f);
        }
    }
}

void System::tick() {
    for(auto obj:gObjects) {
        obj->tick();
    }
}

void System::update() {
    for(auto obj: gObjects) {
        obj->update();
    }
}

void System::render() {
    SDL_RenderClear(gRenderer);
    for(auto obj: gObjects) {
        obj->render(gRenderer);
    }
    SDL_RenderPresent(gRenderer);
}
