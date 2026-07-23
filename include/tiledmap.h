#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <array>
#include <stdexcept>
#include "SDL2/SDL_render.h"
#include "SDL2_image/SDL_image.h"
#include "exceptions.h"
#include "entity.h"

enum Block {
    None,
    CobbledBlock,
    Ladder,
    Building
};

class TiledMap: public Entity {
    SDL_Texture* cblock = nullptr;
    SDL_Texture* ladder = nullptr;
    SDL_Texture* building = nullptr;
    bool loaded = false;
public:
    Block grid[WINDOW_ROWS][WINDOW_COLS];
    TiledMap();
    virtual ~TiledMap();
    void load_media(SDL_Renderer* gRenderer) override;
};

class DemoMap: public TiledMap {
public:
    DemoMap();
    ~DemoMap();
};

#endif
