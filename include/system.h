#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>
#include "exceptions.h"
#include "eventemitter.h"
#include "entity.h"
#include "swordman.h"
#include "canvas.h"
#include "demomap.h"
#include "global.h"

class System {
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool quit, paused;
    Controller controller;
    Viewport viewport;
public:
    static const int PERIOD;
    System() {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw SDL_Cannot_Init(SDL_GetError());
        }
        gWindow = SDL_CreateWindow("Stickman Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
        
        EventEmitter::system_quit->then("quit_main_loop", [this] (const bool&) {
            std::cout << "quiting";
            this->quit = true;
            return true;
        });
        
        EventEmitter::system_pause->then("toggle_system_pause", [this] (const bool&) {
            this->paused = ! this->paused;
            return true;
        });
        
    }
    
    void main_loop() {
        auto d = DemoMap();
        auto s = Swordman(0,0);
        quit = false;
        paused = false;
        while(!quit) {
            EventEmitter::handle_input(quit);
            if(quit) break;
            if(paused) {
                SDL_Delay(PERIOD);
                continue;
            }
            EventEmitter::system_update->notify(true);
            EventEmitter::viewport_update->notify(&viewport);

            SDL_SetRenderDrawColor(gRenderer, 0xd3,0xd3,0xd3,0xff);
            SDL_RenderClear(gRenderer);
            EventEmitter::system_render->notify(&viewport, gRenderer);
            SDL_RenderPresent(gRenderer);
        
            EventEmitter::system_tick->notify(true);
            SDL_Delay(System::PERIOD);
        }
    }
    
    ~System() {
        EventEmitter::system_quit->erase("quit_main_loop");
        EventEmitter::system_pause->erase("toggle_system_pause");
        EventEmitter::viewport_update->erase("update_origin");
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
};

const int System::PERIOD = 16; // this gives u 1000/16 = 60fps

#endif
