#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>
#include "exceptions.h"
#include "gameobject.h"
#include "stickman.h"
#include "vector2d.h"
#include "eventemitter.h"

class System {
    static const int PERIOD;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    int WIDTH, HEIGHT;
    bool quit = false;
public:
    System(int w, int h): WIDTH{w}, HEIGHT{h} {
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
            }
    ~System() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
    
    void main_loop() {
        auto quit_main_loop = EventEmitter::system_quit->then("quit_main_loop", [this] (const bool&) {
            this->quit = true;
            return true;
        });
        while(!quit) {
            EventEmitter::handle_input_events(quit);
            EventEmitter::system_update->notify(true);

            SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
            SDL_RenderFillRect(gRenderer,nullptr);
            EventEmitter::system_render->notify(gRenderer);
            SDL_RenderPresent(gRenderer);

            EventEmitter::system_tick->notify(true);
            SDL_Delay(PERIOD);
        }
    }
    
    void start_demo() {
        auto s = Stickman(20,20,-2,2);
        
        main_loop();
    }
};

const int System::PERIOD = 10;


#endif
