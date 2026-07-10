#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <array>
#include <stdexcept>
#include <SDL2/SDL_pixels.h>
#include "items.h"
#include "global.h"

enum Block {
    None,
    CobbledBlock,
    Ladder,
    Building
};

class TiledMap: Entity {
    SDL_Texture* cblock = nullptr;
    SDL_Texture* ladder = nullptr;
    SDL_Texture* building = nullptr;
    bool loaded = false;
public:
    Block grid[Global::ROWS][Global::COLS];
    static const size_t ROWS, COLS;
    TiledMap(): Entity(EntityRole::CANVAS) {
        for(int r = 0; r < TiledMap::ROWS; r++) {
            for(int c = 0; c < TiledMap::COLS; c++) {
                grid[r][c] = None;
            }
        }
        sprite.add_render_handler("render_tiled_map", [this] (Viewport* vp, SDL_Renderer* gRenderer) {
            this->load_media(gRenderer);
            SDL_Rect src, dest;
            double x, y;
            for(int r=0; r<TiledMap::ROWS; r++) {
                for(int c=0; c<TiledMap::COLS; c++) {
                    x = 64*c;
                    y = 64*r;
                    auto coord = vp->translate({x,y});
                    std::cout << x << " " << y << " " << coord << " vp\n";
                    switch(grid[r][c]) {
                        case None:
                            //std::cout << "none\n";
                            break;
                        case CobbledBlock:
                            src = {0,0,Global::UNIT, Global::UNIT};
                            dest = {0,0,Global::UNIT, Global::UNIT};
                            dest.x = coord.x;
                            dest.y = coord.y;
                            SDL_RenderCopy(gRenderer, this->cblock, &src, &dest);
                            break;
                        case Ladder:
                            dest = {0,0,Global::UNIT, Global::UNIT};
                            dest.x = coord.x;
                            dest.y = coord.y;
                            src = {0,0,107,107};
                            SDL_RenderCopy(gRenderer, this->ladder, &src, &dest);
                            break;
                        case Building:
                            src = {0,0,579,447};
                            dest = {0,0,2*Global::UNIT,2*Global::UNIT};
                            dest.x = coord.x;
                            dest.y = coord.y;
                            SDL_RenderCopy(gRenderer, this->building, nullptr, &dest);
                            break;
                    }
                    
                }
                
            }
            std::cout << "completed\n";
            return true;
        });
    }
    void load_media(SDL_Renderer* gRenderer) override {
        if(loaded) return;
        if(cblock == nullptr) {
            std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/cobbled_block.png";
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            cblock = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        if(ladder == nullptr) {
            std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/ladder.png";
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            ladder = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        if(building == nullptr) {
            std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/building.png";
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            building = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        loaded = true;
        std::cout << "loaded";
    }
};
//const int TiledMap::UNIT = 64;
const size_t TiledMap::ROWS = 12;
const size_t TiledMap::COLS = 24;
#endif
