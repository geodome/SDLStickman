#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"
#include "stickman.h"
#include "position.h"

class System {
    static System* instance;
    static const int DELAY;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    std::vector<GameObject*> game_objects{};
    int WIDTH, HEIGHT;
    
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
public:
    static System* Singleton(int width, int height) {
        if(System::instance == nullptr) System::instance = new System(width,height);
        return System::instance;
    }
    static void Destroy_Singleton() {
        if(System::instance == nullptr) return;
        delete System::instance;
    }
    ~System() {
        while(game_objects.size() > 0) {
            auto ptr = game_objects.back();
            delete ptr;
            game_objects.pop_back();
        }
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
    void tick() {
        for(auto obj: game_objects) {
            obj->animation()->tick();
        }
    }
    void update() {
        for(auto obj: game_objects) {
            obj->animation()->update();
            obj->position()->next();
        }
    }
    void render() {
        //SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
        SDL_RenderFillRect(gRenderer,nullptr);
        for(auto obj: game_objects) {
            obj->animation()->render(gRenderer);
        }
        SDL_RenderPresent(gRenderer);
    }
    void add_game_object(GameObject* ptr) {
        game_objects.push_back(ptr);
    };
    void handle_events(bool& quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
                break;
            }
            if(quit) break;
            for(auto obj: game_objects) {
                obj->controller()->handle_mouse_events(e, quit);
                obj->controller()->handle_keyboard_events(e, quit);
                if(quit) break;
            }
        }
    }
    void main_loop() {
        auto quit = false;
        while(!quit) {
            handle_events(quit);
            if(quit) break;
            update();
            render();
            tick();
            SDL_Delay(DELAY);
        }
    }
    void start_demo() {
        add_game_object(new Stickman(20,20));
        main_loop();
    }
};

const int System::DELAY = 30;
System* System::instance = nullptr;


#endif
