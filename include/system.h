#ifndef SYSTEM_H
#define SYSTEM_H

#include "SDL.h"
#include "exceptions.h"
#include "controller.h"
#include "viewport.h"
#include "eventemitter.h"
#include "global.h"
#include "swordman.h"
#include "tiledmap.h"
#include "swordman.h"

class System {
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool quit, paused;
    Controller controller;
    Viewport viewport;
public:
    static const int PERIOD;
    System();
    ~System();
    void main_loop();
};


#endif
