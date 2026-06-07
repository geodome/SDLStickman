#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

//struct SDL_Event {};

class Animation {
    const int DELAY{100}, WIDTH{403}, HEIGHT{363};
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&,bool&)>>> handlers{};
public:
    Animation();
    ~Animation();
    void main_loop();
    void register_handler(uint32_t, std::function<void(SDL_Event, bool&, bool&)>);
    void handle_events(bool&, bool&);
    void update() {};
    void render() {};
    void add_game_object();
    
};

void Animation::register_handler(uint32_t event_type, std::function<void(SDL_Event, bool&, bool&)> f) {
    handlers[event_type].push_back(f);
}

void Animation::handle_events(bool& quit, bool& suspended) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        for(auto f: handlers[e.type]){
            f(e, quit, suspended);
            if(quit) break;
        }
        if(quit) break;
    }
}

void Animation::main_loop() {
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
        }
        SDL_Delay(DELAY);
    }
}


#endif
