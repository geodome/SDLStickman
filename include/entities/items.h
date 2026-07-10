/*
 #ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <SDL2/SDL.h>
#include "entity.h"
#include "exceptions.h"
#include "global.h"
#include "viewport.h"

class CanvasObject: public Entity {
public:
    CanvasObject() :Entity(EntityRole::CANVAS) {}
    virtual ~CanvasObject() {};
};

class ColoredBlock: public CanvasObject {
    SDL_Color color;
public:
    ColoredBlock(size_t row, size_t col, SDL_Color rgb): color{rgb} {
        position.coord.x = col*Global::UNIT;
        position.coord.y = row*Global::UNIT;
        
        shape.add_render_handler("render_colored_block", [this] (Viewport* vp, SDL_Renderer* gRenderer) {
            SDL_Rect dest{0,0, Global::UNIT, Global::UNIT};
            auto coord = vp->translate(this->position.coord);
            dest.x = coord.x;
            dest.y = coord.y;
            SDL_RenderFillRect(gRenderer, &dest);
            return true;
        });
    };
};

class CobbledBlock: public CanvasObject {
    SDL_Texture* wall = nullptr;
    SDL_Rect src = {0, 0, Global::UNIT, Global::UNIT};
    SDL_Rect dest = {0,0, Global::UNIT, Global::UNIT};
public:
    CobbledBlock(size_t row, size_t col): CanvasObject() {
        sprite.add_render_handler("render_ground", [this, row, col] (Viewport* vp, SDL_Renderer* gRenderer) {
            this->load_media(gRenderer);
            this->dest.x = col*Global::UNIT;
            this->dest.y = row*Global::UNIT;
            SDL_RenderCopy(gRenderer, this->wall, &this->src, &this->dest);
            return true;
        });
    }
    void load_media(SDL_Renderer* gRenderer) override {
        if(wall == nullptr) {
            std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/cobbled_block.png";
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            wall = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
    }
    
    ~CobbledBlock() {
        if(wall != nullptr) SDL_DestroyTexture(wall);
    }
};

class Ladder: public CanvasObject {
    SDL_Texture* ladder = nullptr;
    SDL_Rect src = {0,0,107,107};
    SDL_Rect dest = {0,0, Global::UNIT, Global::UNIT};
public:
    Ladder(size_t row, size_t col): CanvasObject{} {
        position.coord.x = col * Global::UNIT;
        position.coord.y = row * Global::UNIT;
        dest.x = position.coord.x;
        dest.y = position.coord.y;
        sprite.add_render_handler("render_ladder", [this] (SDL_Renderer* gRenderer) {
            this->load_media(gRenderer);
            SDL_RenderCopy(gRenderer, this->ladder, &this->src, &this->dest);
            return true;
        });
    }
    void load_media(SDL_Renderer* gRenderer) override {
        if(ladder == nullptr) {
            std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/ladder.png";
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            ladder = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
    }
    
    ~Ladder() {
        if(ladder != nullptr) SDL_DestroyTexture(ladder);
    }
};

#endif

*/
