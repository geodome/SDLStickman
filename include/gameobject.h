#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "exeptions.h"

class GameObject {
public:
    virtual void draw(SDL_Surface*);
    virtual void render(SDL_Window*);
};



#endif
